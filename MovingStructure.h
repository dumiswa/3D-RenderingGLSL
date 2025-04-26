#ifndef MOVING_STRUCTURE_HPP
#define MOVING_STRUCTURE_HPP

#include "mge/core/GameObject.hpp"

class MovingStructure : public GameObject {
public:
    MovingStructure();
    virtual ~MovingStructure();

private:
    GameObject* child1;
    GameObject* child2;
    GameObject* child3;
};

#endif // MOVING_STRUCTURE_HPP
