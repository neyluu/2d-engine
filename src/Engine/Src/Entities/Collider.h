#ifndef INC_2D_ENGINE_COLLIDER_H
#define INC_2D_ENGINE_COLLIDER_H

#include <vector>
#include <algorithm>

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

    bool isKinematic() const;
    void setKinematic(bool isKinematic);

    bool m_isVisible = false;
protected:
    CanMove m_canMove;
    bool m_isKinematic = false;
private:
    void addTo(std::vector<Collider*>& vector);
    void removeFrom(std::vector<Collider*>& vector);

    friend class ColliderManager;
};


#endif //INC_2D_ENGINE_COLLIDER_H
