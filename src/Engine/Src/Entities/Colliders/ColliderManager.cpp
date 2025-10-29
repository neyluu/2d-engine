#include "ColliderManager.h"

namespace e2d
{
    std::vector<Collider*> ColliderManager::s_kinematicColliders;
    std::vector<Collider*> ColliderManager::s_staticColliders;


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
                    handleCollision(kinematicCollider, staticCollider);
                    staticCollider->pushAway(kinematicCollider);
                }
            }

            for(Collider* otherKinematic : s_kinematicColliders)
            {
                if(kinematicCollider->getId() == otherKinematic->getId() || ! otherKinematic->isActive()) continue;

                if(kinematicCollider->checkCollision(otherKinematic))
                {
                    handleCollision(kinematicCollider, otherKinematic);

                    // Kinematic collider should explicitly perform some action on other kinematic,
                    // so automatic push is disabled
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

    void ColliderManager::handleCollision(Collider* first, Collider* second)
    {
        first->collide();

        first->onCollideEnter();
        first->onCollideEnter(*second);

        first->onCollide();
        first->onCollide(*second);

        // OnExit is called inside Collider update,
        // here only ids of collider for which onExit should be called is added
        first->m_onExitCallsIds.insert(second->getId());


//        TODO CAUSE DOUBLE ON ENTER, BUT WHY?

        second->collide();

        second->onCollideEnter();
        second->onCollideEnter(*first);

        second->onCollide();
        second->onCollide(*first);

        // OnExit is called inside Collider update,
        // here only ids of collider for which onExit should be called is added
        second->m_onExitCallsIds.insert(first->getId());
    }
}

