#include "Collider.h"

namespace e2d
{
    void CanMove::enableAll()
    {
        up = true;
        right = true;
        down = true;
        left = true;
    }

    void Collider::update()
    {
        if(isOnExit())
        {
            onCollideExit();

            for(const int id : m_onExitCallsIds)
            {
                onCollideWithCollider(m_onCollideExitColliders, id);
            }

            m_onExitCallsIds.clear();
        }

        m_wasColliding = m_isCollidingNow;
        m_isCollidingNow = false;
    }

    bool Collider::isKinematic() const
    {
        return m_isKinematic;
    }

    void Collider::setKinematic(bool isKinematic)
    {
        if((m_isKinematic && isKinematic) || ( ! m_isKinematic && ! isKinematic)) return;

        if(m_isKinematic != isKinematic)
        {
            ColliderManager::removeCollider(this);
            m_isKinematic = isKinematic;
            ColliderManager::addCollider(this);
        }
    }

    void Collider::addTo(std::vector<Collider*>& vector)
    {
        vector.push_back(this);
    }

    void Collider::removeFrom(std::vector<Collider*>& vector)
    {
        auto it = std::find(vector.begin(), vector.end(), this);
        if(it != vector.end()) vector.erase(it);
    }

    void Collider::setOnCollideEnter(const std::function<void()>& function)
    {
        m_onCollideEnter = function;
    }

    void Collider::setOnCollideEnter(const std::function<void()>& function, const Collider& collider)
    {
        if(getId() == collider.getId()) return;

        m_onCollideEnterColliders.insert(std::pair(collider.getId(), function));
    }

    void Collider::setOnCollide(const std::function<void()>& function)
    {
        m_onCollide = function;
    }

    void Collider::setOnCollide(const std::function<void()>& function, const Collider& collider)
    {
        if(getId() == collider.getId()) return;

        m_onCollideColliders.insert(std::pair(collider.getId(), function));
    }

    void Collider::setOnCollideExit(const std::function<void()>& function)
    {
        m_onCollideExit = function;
    }

    void Collider::setOnCollideExit(const std::function<void()>& function, const Collider& collider)
    {
        if(getId() == collider.getId()) return;

        m_onCollideExitColliders.insert(std::pair(collider.getId(), function));
    }

    void Collider::collide()
    {
        m_isCollidingNow = true;
    }

    void Collider::onCollideEnter()
    {
        if( ! isOnEnter())
        {
            return;
        }

        if(m_onCollideEnter) m_onCollideEnter();
    }

    void Collider::onCollideEnter(const Collider& collider)
    {
        const int id = collider.getId();

        if( ! isOnEnter() || ! m_onCollideEnterColliders.contains(id))
        {
            return;
        }

        onCollideWithCollider(m_onCollideEnterColliders, id);
    }

    void Collider::onCollide()
    {
        if(m_onCollide)
        {
            m_onCollide();
        }
    }

    void Collider::onCollide(const Collider& collider)
    {
        onCollideWithCollider(m_onCollideColliders, collider.getId());
    }

    void Collider::onCollideExit()
    {
        if(! isOnExit() || ! m_onCollideExit)
        {
            return;
        }

        m_onCollideExit();
    }

    void Collider::onCollideExit(const Collider& collider)
    {
        if(! isOnExit())
        {
            return;
        }

        onCollideWithCollider(m_onCollideExitColliders, collider.getId());
    }

    void Collider::onCollideWithCollider(const std::map<int, std::function<void()>>& map, int id)
    {
        if(map.contains(id))
        {
            const std::function<void()>& function = map.at(id);
            if(function)
            {
                function();
            }
        }
    }

    bool Collider::isOnEnter() const
    {
        return ! m_wasColliding && m_isCollidingNow;
    }

    bool Collider::isOnExit() const
    {
        return m_wasColliding && ! m_isCollidingNow;
    }
}

