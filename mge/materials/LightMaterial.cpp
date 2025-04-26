#include "../../glm.hpp"

#include "LightMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <mge/core/Camera.hpp>


ShaderProgram* LightMaterial::_shader = NULL;

//
//
GLint LightMaterial::_uModelMatrix;
GLint LightMaterial::_uViewMatrix;
GLint LightMaterial::_uProjectionMatrix;

GLint LightMaterial::_uLightPosition;
GLint LightMaterial::_uLightColor;
GLint LightMaterial::_uLightIntensity;

GLint LightMaterial::_uCameraPosition;

GLint LightMaterial::_uMaterialShininess;
GLint LightMaterial::_uMaterialSpecular;
//

GLint LightMaterial::_uMVPMatrix = 0;
GLint LightMaterial::_uDiffuseTexture = 0;

GLint LightMaterial::_aVertex = 0;
GLint LightMaterial::_aNormal = 0;
GLint LightMaterial::_aUV = 0;

LightMaterial::LightMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

LightMaterial::~LightMaterial() {}

void LightMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"light.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"light.fs");
        _shader->finalize();

        //
        _uModelMatrix       = _shader->getUniformLocation("modelMatrix");
        _uViewMatrix        = _shader->getUniformLocation("viewMatrix");
        _uProjectionMatrix  = _shader->getUniformLocation("projectionMatrix");

        _uLightPosition     = _shader->getUniformLocation("lightPosition");
        _uLightColor        = _shader->getUniformLocation("lightColor");
        _uLightIntensity    = _shader->getUniformLocation("lightIntensity");

        _uCameraPosition    = _shader->getUniformLocation("cameraPosition");

        _uMaterialShininess = _shader->getUniformLocation("materialShininess");
        _uMaterialSpecular  = _shader->getUniformLocation("materialSpecular");
        //

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void LightMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    //
    // Set transformation matrices
    glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
    glUniformMatrix4fv(_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));

    // Set light properties from the scene
    if (pWorld->getLightCount() > 0) {
        Light* light = pWorld->getLightAt(0);
        glm::vec3 lightPos = light->getWorldTransform()[3]; // extract world position from transform matrix
        glUniform3fv(_uLightPosition, 1, glm::value_ptr(lightPos));
        glUniform3fv(_uLightColor, 1, glm::value_ptr(glm::vec3(1.0f))); // white light for now
        glUniform1f(_uLightIntensity, 5.0f);
    }

    // Set camera position
    glUniform3fv(_uCameraPosition, 1, glm::value_ptr(pWorld->getMainCamera()->getWorldPosition()));

    // Set material properties
    glUniform1f(_uMaterialShininess, _shininess);
    glUniform3fv(_uMaterialSpecular, 1, glm::value_ptr(_specularColor));
    //


    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
