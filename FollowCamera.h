#ifndef FOLLOW_CAMERA_HPP
#define FOLLOW_CAMERA_HPP

#include "mge/core/Camera.hpp"
#include "glm.hpp"

class FollowCamera : public Camera {
public:
    FollowCamera(GameObject* target);
    virtual void update(float deltaTime) override;

private:
    GameObject* _target;
    float _distance;
};

#endif // FOLLOW_CAMERA_HPP

