#ifndef INC_2D_ENGINE_COLLIDER_H
#define INC_2D_ENGINE_COLLIDER_H

#include "Drawable.h"
#include "ColliderManager.h"

struct CanMove
{
    bool up = true;
    bool right = true;
    bool down = true;
    bool left = true;

    void enableAll();
};

class BoxCollider;
class CircleCollider;

class Collider : public Drawable
{
public:
    ~Collider() override = default;

    virtual bool checkCollision(Collider* other) = 0;
    virtual bool collideWith(BoxCollider* other) = 0;
    virtual bool collideWith(CircleCollider* other) = 0;

    virtual void moveFrom(Collider* other) = 0;
    virtual void moveFrom(BoxCollider* other) = 0;
    virtual void moveFrom(CircleCollider* other) = 0;

    bool m_isVisible = false;
    bool m_isKinematic = false;
protected:
    CanMove canMove;
private:
};


#endif //INC_2D_ENGINE_COLLIDER_H
