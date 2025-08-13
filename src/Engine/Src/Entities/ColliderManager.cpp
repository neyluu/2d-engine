#include "ColliderManager.h"

std::vector<Collider*> ColliderManager::m_colliders;

void ColliderManager::update()
{
    for(Collider* kinematicCollider : m_colliders)
    {
        if( ! kinematicCollider->m_isKinematic || ! kinematicCollider->isActive()) continue;

        for(Collider* staticCollider : m_colliders)
        {
            if(staticCollider == kinematicCollider || ! staticCollider->isActive()) continue;

            if(kinematicCollider->checkCollision(staticCollider))
            {
                staticCollider->moveFrom(kinematicCollider);
            }
        }
    }
}

void ColliderManager::addCollider(Collider* collider)
{
    ColliderManager::m_colliders.push_back(collider);
}