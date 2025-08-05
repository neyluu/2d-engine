#include "Scene.h"

void Scene::update()
{
    for(GameObject* object : m_allObjects)
    {
        if(object->isActive()) object->update();
    }
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
    if(auto drawable = dynamic_cast<Drawable*>(object))
    {
        m_allDrawables.push_back(drawable);
    }

    m_allObjects.push_back(object);
}