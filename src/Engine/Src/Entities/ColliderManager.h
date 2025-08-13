#ifndef INC_2D_ENGINE_COLLIDERMANAGER_H
#define INC_2D_ENGINE_COLLIDERMANAGER_H

#include <vector>
#include <iostream>

#include "Collider.h"

class Collider;

class ColliderManager
{
public:
    void update();

    static void addCollider(Collider* collider);
    static std::vector<Collider*> m_colliders;
};

#endif //INC_2D_ENGINE_COLLIDERMANAGER_H
