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

    void setScene(Scene* scene);

    int getId() const;

protected:
    GameObject();
    Scene* m_owner = nullptr;
    int m_id = 0;

private:
    bool m_isActive = true;
    inline static int s_lastId = 0;
};


#endif //INC_2D_ENGINE_GAMEOBJECT_H
