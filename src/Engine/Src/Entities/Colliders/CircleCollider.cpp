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
        if( ! isVisible) return;

        DrawCircle(transform.position.x, transform.position.y, m_radius, WHITE);
        DrawCircle(transform.position.x, transform.position.y, 2, GREEN);
    }

    bool CircleCollider::checkCollision(Collider *other)
    {
        m_canMove.enableAll();
        return other->collideWith(this);
    }

    bool CircleCollider::collideWith(BoxCollider *other)
    {
        return CheckCollisionCircleRec(transform.position, (float) m_radius, other->getBox());
    }

    bool CircleCollider::collideWith(CircleCollider *other)
    {
        return CheckCollisionCircles(transform.position, m_radius, other->transform.position, other->getRadius());
    }

    void CircleCollider::pushAway(Collider *other)
    {
        if(m_isTrigger) return;
        other->moveFrom(this);
    }

    void CircleCollider::moveFrom(BoxCollider *other)
    {
        Rectangle box = other->getBox();

        float closestX = fmaxf(box.x, fminf(transform.position.x, box.x + box.width));
        float closestY = fmaxf(box.y, fminf(transform.position.y, box.y + box.height));

        float dx = transform.position.x - closestX;
        float dy = transform.position.y - closestY;

        float distance = sqrtf(dx * dx + dy * dy);
        float overlap = m_radius - distance;

        if(overlap > 0.0f)
        {
            const float epsilon = 1e-6f;

            if(distance > epsilon)
            {
                float nx = dx / distance;
                float ny = dy / distance;

                transform.position.x += nx * overlap;
                transform.position.y += ny * overlap;
            }
            else
            {
                float leftDistance   = transform.position.x - box.x;
                float rightDistance  = (box.x + box.width) - transform.position.x;
                float topDistance    = transform.position.y - box.y;
                float bottomDistance = (box.y + box.height) - transform.position.y;

                float minDistance = leftDistance;
                enum Side { LEFT, RIGHT, TOP, BOTTOM } side = LEFT;

                if(rightDistance < minDistance)
                {
                    minDistance = rightDistance;
                    side = RIGHT;
                }
                if(topDistance < minDistance)
                {
                    minDistance = topDistance;
                    side = TOP;
                }
                if(bottomDistance < minDistance)
                {
                    minDistance = bottomDistance;
                    side = BOTTOM;
                }

                switch (side)
                {
                    case LEFT:
                        transform.position.x = box.x - m_radius - 1e-3f;
                        break;
                    case RIGHT:
                        transform.position.x = box.x + box.width + m_radius + 1e-3f;
                        break;
                    case TOP:
                        transform.position.y = box.y - m_radius - 1e-3f;
                        break;
                    case BOTTOM:
                        transform.position.y = box.y + box.height + m_radius + 1e-3f;
                        break;
                }
            }
        }
    }

    void CircleCollider::moveFrom(CircleCollider *other)
    {
        float distance = Vector2Distance(transform.position, other->transform.position);
        Vector2 direction = { transform.position.x - other->transform.position.x, transform.position.y - other->transform.position.y };
        float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

        if(length != 0.0f)
        {
            direction.x /= length;
            direction.y /= length;
        }

        float overlap = (m_radius + other->getRadius()) - distance;
        if (overlap > 0.0f)
        {
            transform.position.x += direction.x * overlap;
            transform.position.y += direction.y * overlap;
        }
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