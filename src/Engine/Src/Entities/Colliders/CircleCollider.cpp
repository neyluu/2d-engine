#include "CircleCollider.h"

namespace e2d
{
    CircleCollider::CircleCollider(int radius)
    {
        m_radius = radius;
    }

    void CircleCollider::update()
    {

    }

    void CircleCollider::draw()
    {
        DrawCircle(transform.position.x, transform.position.y, m_radius, WHITE);
        DrawCircle(transform.position.x, transform.position.y, 2, GREEN);
    }

    bool CircleCollider::checkCollision(e2d::Collider *other)
    {

    }

    bool CircleCollider::collideWith(e2d::BoxCollider *other)
    {
        return false;
    }

    bool CircleCollider::collideWith(e2d::CircleCollider *other)
    {
        return false;

    }

    void CircleCollider::pushAway(e2d::Collider *other)
    {

    }

    void CircleCollider::moveFrom(e2d::BoxCollider *other)
    {

    }

    void CircleCollider::moveFrom(e2d::CircleCollider *other)
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