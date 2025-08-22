#ifndef INC_2D_ENGINE_SCENE_H
#define INC_2D_ENGINE_SCENE_H

#include <memory>
#include <list>
#include <iostream>

#include "../Entities/GameObject.h"
#include "../Entities/Drawable.h"
#include "Entities/Colliders/Collider.h"
#include "Entities/Colliders/ColliderManager.h"

namespace e2d
{
    class Scene
    {
    public:
        Scene() = default;

        void update();
        void draw();

        void addObject(GameObject* object);
        void sortDrawables();

    private:
        void insertDrawableSorted(Drawable* drawable);

        ColliderManager m_colliderManager;

        std::list<GameObject*> m_allObjects;
        std::list<Drawable*> m_allDrawables;
    };
}

#endif //INC_2D_ENGINE_SCENE_H
