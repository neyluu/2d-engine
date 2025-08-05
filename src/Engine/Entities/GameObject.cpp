#include "GameObject.h"

void GameObject::enable()
{
    m_isActive = true;
}

void GameObject::disable()
{
    m_isActive = false;
}

bool GameObject::isActive() const
{
    return m_isActive;
}
