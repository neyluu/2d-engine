#include "CircleCollider.h"

namespace e2d
{
    CircleCollider::CircleCollider(int radius)
    {
        m_radius = radius;
    }

    void CircleCollider::update()
    {
        Collider::update();
    }

    void CircleCollider::draw()
    {
        if( ! m_isVisible) return;

        DrawCircle(transform.position.x, transform.position.y, m_radius, WHITE);
        DrawCircle(transform.position.x, transform.position.y, 2, GREEN);
    }

    bool CircleCollider::checkCollision(Collider *other)
    {

    }

    bool CircleCollider::collideWith(BoxCollider *other)
    {
        return CheckCollisionCircleRec(transform.position, (float) m_radius, other->getBox());
    }

    bool CircleCollider::collideWith(CircleCollider *other)
    {
        return false;
    }

    void CircleCollider::pushAway(Collider *other)
    {
        other->moveFrom(this);
    }

    void CircleCollider::moveFrom(BoxCollider *other)
    {
    }

    void CircleCollider::moveFrom(CircleCollider *other)
    {

    }

    void CircleCollider::setRadius(int radius)
    {
        m_radius = radius;
    }

    int CircleCollider::getRadius()
    {
        return m_radius;
    }
}