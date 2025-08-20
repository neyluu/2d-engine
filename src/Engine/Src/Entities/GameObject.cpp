#include "GameObject.h"

GameObject::GameObject()
{
    m_id = s_lastId++;
}

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

void GameObject::setScene(Scene *scene)
{
    this->m_owner = scene;
}

int GameObject::getId() const
{
    return m_id;
}