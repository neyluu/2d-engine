#include "Collider.h"

void CanMove::enableAll()
{
    up = true;
    right = true;
    down = true;
    left = true;
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

