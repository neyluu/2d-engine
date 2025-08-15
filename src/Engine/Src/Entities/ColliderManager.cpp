#include "ColliderManager.h"

std::vector<Collider*> ColliderManager::s_staticColliders;
std::vector<Collider*> ColliderManager::s_kinematicColliders;

void ColliderManager::update()
{
    for(Collider* kinematicCollider : s_kinematicColliders)
    {
        if( ! kinematicCollider->isActive()) continue;

        for(Collider* staticCollider : s_staticColliders)
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
    collider->addTo((collider->isKinematic()) ? s_kinematicColliders : s_staticColliders);
}

void ColliderManager::removeCollider(Collider* collider)
{
    collider->removeFrom((collider->isKinematic()) ? s_kinematicColliders : s_staticColliders);
}