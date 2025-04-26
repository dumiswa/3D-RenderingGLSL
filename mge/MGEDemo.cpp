#include "mge/MGEDemo.hpp"
#include "config.hpp"
#include "MovingStructure.h"
#include "FollowCamera.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/World.hpp"
#include "mge/util/DebugHud.hpp"
#include "mge/core/Light.hpp"
#include "materials/ColorMaterial.hpp"
#include "behaviours/KeysBehaviour.hpp"
#include "behaviours/RotatingBehaviour.hpp"
#include "materials/LightMaterial.hpp"
#include "materials/TerrainMaterial.h"

MGEDemo::MGEDemo() : AbstractGame(), _hud(0) {}

void MGEDemo::initialize()
{
    AbstractGame::initialize();
    _hud = new DebugHud(_window);
}

void MGEDemo::_initializeScene()
{
    int assignmentToBuild = 4;

    if (assignmentToBuild == 2)
    {
        Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane20x20_2048tris_aligned_uvs.obj");
        Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");

        AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
        AbstractMaterial* runicStoneMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"runicfloor.png"));

        GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
        plane->scale(glm::vec3(5,5,5));
        plane->setMesh(planeMeshDefault);
        plane->setMaterial(runicStoneMaterial);
        _world->add(plane);

        //moving Structure
        MovingStructure* structure = new MovingStructure();
        structure->setLocalPosition(glm::vec3(0, 0, 0));
        structure->rotate(15.0f, glm::vec3(0, 1, 0));
        _world->add(structure);

        //follow Camera
        FollowCamera* camera = new FollowCamera(structure);
        _world->add(camera);
        _world->setMainCamera(camera);

        Light* light = new Light("light", glm::vec3(0,4,0));
        light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
        light->setMesh(cubeMeshF);
        light->setMaterial(lightMaterial);
        //light->setBehaviour(new KeysBehaviour(25));
        _world->add(light);
    }

    if (assignmentToBuild == 3)
    {
        //MESHES
        Mesh* sphereMesh = Mesh::load (config::MGE_MODEL_PATH + "sphere_smooth.obj");
        Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
        Texture* bricksTex = Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg");
        Texture* planeTex = Texture::load(config::MGE_TEXTURE_PATH + "land.jpg");


        /*GameObject* plane = new GameObject("plane", glm::vec3(0, 1, 0));
        //plane->rotate(0.0f, glm::vec3(0, 0, 0));
        plane->setMesh(planeMesh);
        plane->setMaterial(new LightMaterial(planeTex));
        _world->add(plane);*/

        //MATERIAL
        AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
        LightMaterial* litMat = new LightMaterial(bricksTex);

        //OBJECT
        GameObject* litObject = new GameObject("LitCube", glm::vec3(0, 0, 0));
        litObject->setMesh(sphereMesh);
        litObject->setMaterial(litMat);
        litObject->setBehaviour(new RotatingBehaviour);
        _world->add(litObject);

        //CAMERA
        Camera* cam = new Camera("MainCamera", glm::vec3(0, 3, 8));
        cam->rotate(glm::radians(-20.0f), glm::vec3(1, 0, 0));
        _world->add(cam);
        _world->setMainCamera(cam);

        //LIGHT
        Light* light = new Light("MainLight", glm::vec3(0, 5, 5));
        light->setMesh(sphereMesh);
        light->setMaterial(lightMaterial);
        light->setBehaviour(new KeysBehaviour(25));
        _world->add(light);

    }

    if (assignmentToBuild == 4)
    {
        // Load mesh
        Mesh* terrainMesh = Mesh::load(config::MGE_MODEL_PATH + "plane20x20_2048tris_aligned_uvs.obj");

        // Load textures
        Texture* heightmap = Texture::load(config::MGE_TEXTURE_PATH + "heightmap.png");
        Texture* splatmap  = Texture::load(config::MGE_TEXTURE_PATH + "splatmap.png");

        std::vector<Texture*> layers = {
            Texture::load(config::MGE_TEXTURE_PATH + "diffuse1.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH + "diffuse4.jpg")
        };

        TerrainMaterial* terrainMat = new TerrainMaterial(heightmap, layers, splatmap);

        GameObject* terrain = new GameObject("Terrain");
        terrain->setMesh(terrainMesh);
        terrain->setMaterial(terrainMat);
        terrain->rotate(glm::radians(-45.0f), glm::vec3(0, 1, 0));
        //terrain->setBehaviour(new RotatingBehaviour);
        _world->add(terrain);

        // Camera
        Camera* cam = new Camera("TerrainCamera", glm::vec3(0, 6, 18));
        cam->rotate(glm::radians(-30.0f), glm::vec3(1, 0, 0)); // Tilt down
        //cam->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));  // Rotate sideways if needed
        _world->add(cam);
        _world->setMainCamera(cam);
    }
}

void MGEDemo::_render()
{
    AbstractGame::_render();
    if (_hud) _hud->draw();
}

MGEDemo::~MGEDemo() {}
