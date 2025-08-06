#ifndef INC_2D_ENGINE_GAMEOBJECT_H
#define INC_2D_ENGINE_GAMEOBJECT_H

class Scene;

class GameObject
{
public:
    virtual ~GameObject() = default;

    virtual void update() = 0;

    void enable();
    void disable();
    bool isActive() const;

protected:
    GameObject() { };
private:

    bool m_isActive = true;
};


#endif //INC_2D_ENGINE_GAMEOBJECT_H
