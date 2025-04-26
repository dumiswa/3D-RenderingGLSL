#include "MovingStructure.h"
#include "mge/config.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"

MovingStructure::MovingStructure() : GameObject("RootStructure")
{
    setBehaviour(new KeysBehaviour(20.0f));

    Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
    Mesh* cylinderMesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");

    AbstractMaterial* redMaterial = new ColorMaterial(glm::vec3(1, 0, 0));
    AbstractMaterial* blueMaterial = new ColorMaterial(glm::vec3(0, 0, 1));
    AbstractMaterial* texture1 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
    AbstractMaterial* texture2 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));

    child1 = new GameObject("Child1");
    child1->setLocalPosition(glm::vec3(0, 0, 0));
    child1->setMesh(sphereMesh);
    child1->setMaterial(redMaterial);
    add(child1); // Attach to Root(0, 0, 0)

    child2 = new GameObject("Child2");
    child2->setLocalPosition(glm::vec3(0, 2.5, 0)); // Position relative to Child1
    child2->setMesh(cylinderMesh);
    child2->setMaterial(texture2);
    child1->add(child2);

    child3 = new GameObject("Child3");
    child3->setLocalPosition(glm::vec3(0, 2.5, 0));
    child3->setMesh(cubeMesh);
    child3->setMaterial(texture1);
    child2->add(child3);
}

MovingStructure::~MovingStructure()
{
    delete child1;
    delete child2;
    delete child3;
}
