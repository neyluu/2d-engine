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
    static void removeCollider(Collider* collider);
private:
    void handleCollision(Collider* first, Collider* second);

    static std::vector<Collider*> s_staticColliders;
    static std::vector<Collider*> s_kinematicColliders;
};

#endif //INC_2D_ENGINE_COLLIDERMANAGER_H
