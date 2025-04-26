#include "TerrainMaterial.h"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
#include <glm/gtc/type_ptr.hpp>

ShaderProgram* TerrainMaterial::_shader = nullptr;

GLint TerrainMaterial::_uModel, TerrainMaterial::_uView, TerrainMaterial::_uProj;
GLint TerrainMaterial::_uHeightmap, TerrainMaterial::_uSplatmap;
GLint TerrainMaterial::_uHeightMultiplier;
GLint TerrainMaterial::_uDiffuse[4];
GLint TerrainMaterial::_uLightDir;
GLint TerrainMaterial::_aVertex, TerrainMaterial::_aNormal, TerrainMaterial::_aUV;

TerrainMaterial::TerrainMaterial(Texture* heightmap, std::vector<Texture*> layers, Texture* splatmap)
    : _heightmap(heightmap), _layers(layers), _splatmap(splatmap)
{
    _lazyInitShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitShader() {
    if (_shader) return;

    _shader = new ShaderProgram();
    _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vs");
    _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.fs");
    _shader->finalize();

    _uModel = _shader->getUniformLocation("modelMatrix");
    _uView = _shader->getUniformLocation("viewMatrix");
    _uProj = _shader->getUniformLocation("projectionMatrix");
    _uHeightmap = _shader->getUniformLocation("heightmap");
    _uHeightMultiplier = _shader->getUniformLocation("heightMultiplier");
    _uSplatmap = _shader->getUniformLocation("splatmap");

    _uDiffuse[0] = _shader->getUniformLocation("diffuse1");
    _uDiffuse[1] = _shader->getUniformLocation("diffuse2");
    _uDiffuse[2] = _shader->getUniformLocation("diffuse3");
    _uDiffuse[3] = _shader->getUniformLocation("diffuse4");

    _uLightDir = _shader->getUniformLocation("lightDir");

    _aVertex = _shader->getAttribLocation("vertex");
    _aNormal = _shader->getAttribLocation("normal");
    _aUV = _shader->getAttribLocation("uv");
}

void TerrainMaterial::render(World* world, Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    _shader->use();

    //upolad matrices
    glUniformMatrix4fv(_uModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(_uView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(_uProj, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(_uHeightMultiplier, _heightMultiplier);

    //light direction
    //glUniform3fv(_uLightDir, 1, glm::value_ptr(glm::vec3(-1, -1, -1)));

    //bind heightmap
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _heightmap->getId());
    glUniform1i(_uHeightmap, 0);

    //bind terrain textures
    for (int i = 0; i < 4; ++i) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, _layers[i]->getId());
        glUniform1i(_uDiffuse[i], 1 + i);
    }

    // bind splatmap
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, _splatmap->getId());
    glUniform1i(_uSplatmap, 5);

    //send to gpu
    mesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
