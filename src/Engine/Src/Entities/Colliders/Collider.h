#ifndef INC_2D_ENGINE_COLLIDER_H
#define INC_2D_ENGINE_COLLIDER_H

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

#include "Entities/Drawable.h"
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

    void setOnCollideEnter(const std::function<void()>& function);
    void setOnCollide(const std::function<void()>& function);
    void setOnCollideExit(const std::function<void()>& function);
    void setOnCollideEnter(const std::function<void()>& function, const Collider& collider);
    void setOnCollide(const std::function<void()>& function, const Collider& collider);
    void setOnCollideExit(const std::function<void()>& function, const Collider& collider);

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

    void onCollideEnter();
    void onCollide();
    void onCollideExit();
    void onCollideEnter(const Collider& collider);
    void onCollide(const Collider& collider);
    void onCollideExit(const Collider& collider);

    bool isOnEnter() const;
    bool isOnExit() const;

    void onCollideWithCollider(const std::map<int, std::function<void()>>& map, int id);

    std::function<void()> m_onCollideEnter;
    std::function<void()> m_onCollide;
    std::function<void()> m_onCollideExit;

    bool m_wasColliding = false; // Last frame
    bool m_isCollidingNow = false;

    std::set<int> m_onExitCallsIds;

    std::map<int, std::function<void()>> m_onCollideEnterColliders;
    std::map<int, std::function<void()>> m_onCollideColliders;
    std::map<int, std::function<void()>> m_onCollideExitColliders;

    friend class ColliderManager;
};


#endif //INC_2D_ENGINE_COLLIDER_H
