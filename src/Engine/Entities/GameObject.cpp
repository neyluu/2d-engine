#include "GameObject.h"

std::list<GameObject*> GameObject::g_gameObjects;

std::list<GameObject*> GameObject::m_disabledGameObjects;
std::list<GameObject*> GameObject::m_shouldBeDisabled;

GameObject::GameObject()
{
    m_self = g_gameObjects.insert(g_gameObjects.end(), this);
}

GameObject::~GameObject()
{
    if(m_isActive)  g_gameObjects.erase(m_self);
    else            m_disabledGameObjects.erase(m_self);
}

void GameObject::enable()
{
    if(m_isActive) return;

    m_isActive = true;
    m_disabledGameObjects.erase(m_self);
    m_self = g_gameObjects.insert(g_gameObjects.end(), this);
}

void GameObject::disable()
{
    if(! m_isActive) return;

    m_isActive = false;
    g_gameObjects.erase(m_self);
    m_self = m_disabledGameObjects.insert(m_disabledGameObjects.end(), this);
}

void GameObject::requestDisable()
{
    m_shouldBeDisabled.push_back(this);
}

void GameObject::disableRequested()
{
    for(auto object : m_shouldBeDisabled)
    {
        object->disable();
    }
}
