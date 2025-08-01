#ifndef INC_2D_ENGINE_GAMEOBJECT_H
#define INC_2D_ENGINE_GAMEOBJECT_H

#include <list>
#include <iostream>


class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void update() = 0;
    virtual void draw() = 0;

    void enable();
    void disable(); // Should not be called inside update()

    static void disableRequested();

    static std::list<GameObject*> g_gameObjects;
protected:
    void requestDisable();
private:
    std::list<GameObject*>::iterator m_self {};
    static std::list<GameObject*> m_disabledGameObjects;
    static std::list<GameObject*> m_shouldBeDisabled;
    bool m_isActive = true;
};


#endif //INC_2D_ENGINE_GAMEOBJECT_H
