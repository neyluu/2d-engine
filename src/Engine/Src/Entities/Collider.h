#ifndef INC_2D_ENGINE_COLLIDER_H
#define INC_2D_ENGINE_COLLIDER_H

#include <vector>
#include <algorithm>
#include <functional>

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

    void update() override;

    virtual bool checkCollision(Collider* other) = 0;
    virtual bool collideWith(BoxCollider* other) = 0;
    virtual bool collideWith(CircleCollider* other) = 0;

    virtual void pushAway(Collider* other) = 0;
    virtual void moveFrom(BoxCollider* other) = 0;
    virtual void moveFrom(CircleCollider* other) = 0;

    void setOnCollide(const std::function<void()>& function);
    void setOnCollideUpdate(const std::function<void()>& function);
    void setOnCollideExit(const std::function<void()>& function);

    bool isKinematic() const;
    void setKinematic(bool isKinematic);

    bool m_isVisible = false;
protected:
    CanMove m_canMove;
    bool m_isKinematic = false;
private:
    void addTo(std::vector<Collider*>& vector);
    void removeFrom(std::vector<Collider*>& vector);

    void collide();

    void onCollide();
    void onCollideUpdate();
    void onCollideExit();

    std::function<void()> m_onCollide;
    std::function<void()> m_onCollideUpdate;
    std::function<void()> m_onCollideExit;

    bool m_wasColliding = false; // Last frame
    bool m_isCollidingNow = false;
    bool m_collideEntered = false;

    friend class ColliderManager;
};


#endif //INC_2D_ENGINE_COLLIDER_H
