#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "AbstractMaterial.hpp"
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>

class ShaderProgram;
class Texture;

class TerrainMaterial : public AbstractMaterial {
public:
    TerrainMaterial(Texture* heightmap, std::vector<Texture*> layers, Texture* splatmap);
    virtual ~TerrainMaterial();

    virtual void render(World* world, Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

private:
    static ShaderProgram* _shader;
    static void _lazyInitShader();

    Texture* _heightmap;
    std::vector<Texture*> _layers;
    Texture* _splatmap;

    float _heightMultiplier = 5.0f;

    //matrices
    static GLint _uModel;
    static GLint _uView;
    static GLint _uProj;

    static GLint _uHeightmap;
    static GLint _uHeightMultiplier;
    static GLint _uSplatmap;

    static GLint _uDiffuse[4];

    static GLint _uLightDir;

    static GLint _aVertex;
    static GLint _aNormal;
    static GLint _aUV;
};

#endif
