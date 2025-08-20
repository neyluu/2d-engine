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

                if(staticCollider->m_onCollideEnter)
                    staticCollider->m_onCollideEnter();
                if(kinematicCollider->m_onCollideEnter)
                    kinematicCollider->m_onCollideEnter();

                staticCollider->pushAway(kinematicCollider);
            }


//            kinematicCollider->onCollide(staticCollider);
        }

        for(Collider* otherKinematic : s_kinematicColliders)
        {
            if(kinematicCollider->getId() == otherKinematic->getId() || ! otherKinematic->isActive()) continue;

            if(kinematicCollider->checkCollision(otherKinematic))
            {
                kinematicCollider->collide();

                kinematicCollider->onCollideEnter();
                kinematicCollider->onCollideEnter(*otherKinematic);

                kinematicCollider->onCollide();
                kinematicCollider->onCollide(*otherKinematic);

                // OnExit is called inside Collider update,
                // here only ids of collider for which onExit should be called is added
                kinematicCollider->m_onExitCallsIds.insert(otherKinematic->getId());

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