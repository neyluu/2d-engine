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
                // both colliding -> collider method that will handle everything ??

                if(staticCollider->m_onCollide)
                    staticCollider->m_onCollide();
                if(kinematicCollider->m_onCollide)
                    kinematicCollider->m_onCollide();

                staticCollider->pushAway(kinematicCollider);
            }
        }

        for(Collider* otherKinematic : s_kinematicColliders)
        {
            if(kinematicCollider == otherKinematic || ! otherKinematic->isActive()) continue;

            if(kinematicCollider->checkCollision(otherKinematic))
            {
                // both colliding -> collider method that will handle everything ??

                kinematicCollider->collide();
                otherKinematic->collide();

                kinematicCollider->onCollide();
                kinematicCollider->onCollideUpdate();
//                kinematicCollider->onCollideExit();

                otherKinematic->onCollide();
                otherKinematic->onCollideUpdate();
//                otherKinematic->onCollideExit();

//                staticCollider->pushAway(kinematicCollider);
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