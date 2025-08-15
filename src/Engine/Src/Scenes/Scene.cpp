#include "Scene.h"

bool compareDrawables(const Drawable* first, const Drawable* second)
{
    return first->getDepth() < second->getDepth();
}

void Scene::update()
{
    for(GameObject* object : m_allObjects)
    {
        if(object->isActive()) object->update();
    }

    m_colliderManager.update();
}

void Scene::draw()
{
    for(Drawable* drawable : m_allDrawables)
    {
        if(drawable->isActive()) drawable->draw();
    }
}

void Scene::addObject(GameObject* object)
{
    object->setScene(this);

    if(auto drawable = dynamic_cast<Drawable*>(object))
    {
        m_allDrawables.push_back(drawable);
        sortDrawables();
    }
    if(auto collider = dynamic_cast<Collider*>(object))
    {
        ColliderManager::addCollider(collider);
    }

    m_allObjects.push_back(object);
}

void Scene::sortDrawables()
{
    m_allDrawables.sort(compareDrawables);
}

void Scene::insertDrawableSorted(Drawable* drawable)
{
    if(drawable->getDepth() < m_allDrawables.front()->getDepth())
    {
        m_allDrawables.push_front(drawable);
    }
    if(drawable->getDepth() > m_allDrawables.back()->getDepth())
    {
        m_allDrawables.push_back(drawable);
    }
}