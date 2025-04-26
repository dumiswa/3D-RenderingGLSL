#include "FollowCamera.h"
#include "glm/gtc/matrix_transform.hpp"

FollowCamera::FollowCamera(GameObject* target)
    : Camera("FollowCamera", target->getLocalPosition() + glm::vec3(0, 5, 15),
        glm::perspective(glm::radians(60.0f), 4.0f/3.0f, 0.1f, 1000.0f)),
        _target(target), _distance(15.0f) {}

void FollowCamera::update(float deltaTime)
{
    if (_target)
    {
        glm::vec3 targetPos = _target->getLocalPosition();
        glm::vec3 cameraPos = targetPos + glm::vec3(0, 5, _distance);
        glm::vec3 upVector = glm::vec3(0, 1, 0);

        //compute "look at" transformation
        glm::mat4 viewMatrix = glm::lookAt(cameraPos, targetPos, upVector);

        //set camera transform (without rotating with the object)
        setTransform(glm::inverse(viewMatrix));
    }
}
