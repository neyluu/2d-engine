#include "Collider.h"

void CanMove::enableAll()
{
    up = true;
    right = true;
    down = true;
    left = true;
}

void Collider::update()
{
    if(m_isCollidingNow) onCollideUpdate();
//    if(!isKinematic()) return;
//    std::cout << "colliding: " << m_colliding << "\n";

    onCollideExit();
    // necessary !!!

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

void Collider::setOnCollide(const std::function<void()>& function)
{
    this->m_onCollide = function;
}

void Collider::setOnCollideUpdate(const std::function<void()>& function)
{
    this->m_onCollideUpdate = function;
}

void Collider::setOnCollideExit(const std::function<void()>& function)
{
    this->m_onCollideExit = function;
}

void Collider::collide()
{
    m_wasColliding = m_isCollidingNow;
    m_isCollidingNow = true;
}

void Collider::onCollide()
{
    if(m_collideEntered) return;

    m_collideEntered = true;
    if(m_onCollide) m_onCollide();

    std::cout << std::boolalpha;
    std::cout << m_collideEntered << " " << m_wasColliding << " " << m_isCollidingNow << "\n";

    std::cout << "onColliderEnter!\n";
}

void Collider::onCollideUpdate()
{
    if(m_onCollideUpdate) m_onCollideUpdate();

    std::cout << "onColliderUPDATE!\n";
}

void Collider::onCollideExit()
{
    if(!m_isCollidingNow && m_wasColliding)
    {
        m_wasColliding = false;
        std::cout << "onCollideEXIT!!!!!!!\n";
        m_collideEntered = false;
    }
}
