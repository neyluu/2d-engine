#include "BoxCollider.h"

namespace e2d
{
    BoxCollider::BoxCollider(int width, int height)
    {
        m_size.x = width;
        m_size.y = height;

        m_box.width = width;
        m_box.height = height;
    }

    void BoxCollider::update()
    {
        Collider::update();

        m_box.width  = m_size.x * transform.scale.x;
        m_box.height = m_size.y * transform.scale.y;

        m_box.x = transform.position.x - (m_box.width / 2.0f);
        m_box.y = transform.position.y - (m_box.height / 2.0f);
    }

    void BoxCollider::draw()
    {
        if( ! m_isVisible) return;

        DrawRectangle(m_box.x, m_box.y, m_box.width, m_box.height, WHITE);
        DrawRectangleLinesEx(m_box, 2, RED);

        DrawCircle(transform.position.x, transform.position.y, 2, GREEN);
        DrawCircle(m_box.x, m_box.y, 2, ORANGE);
    }

    Rectangle BoxCollider::getBox()
    {
        return m_box;
    }

    bool BoxCollider::checkCollision(Collider* other)
    {
        m_canMove.enableAll();
        return other->collideWith(this);
    }

    bool BoxCollider::collideWith(BoxCollider* other)
    {
        return (
            m_box.x < other->m_box.x + other->m_box.width &&
            m_box.x + m_box.width > other->m_box.x &&
            m_box.y < other->m_box.y + other->m_box.height &&
            m_box.y + m_box.height > other->m_box.y
        );
    }

    bool BoxCollider::collideWith(CircleCollider* other)
    {
//        int px = std::max(m_box.x, std::min(other->transform.position.x, m_box.x + m_size.x));
//        int py = std::max(m_box.y, std::min(other->transform.position.y, m_box.y + m_size.y));

//        std::cout << "px py " << px << " " << py << '\n';

        return false;
    }

    void BoxCollider::pushAway(Collider* other)
    {
        other->moveFrom(this);
    }

    void BoxCollider::moveFrom(BoxCollider* other)
    {
        float thisCenterX = m_box.x + m_box.width  * 0.5f;
        float thisCenterY = m_box.y + m_box.height * 0.5f;
        float otherCenterX = other->m_box.x + other->m_box.width  * 0.5f;
        float otherCenterY = other->m_box.y + other->m_box.height * 0.5f;

        float halfWidth  = m_box.width  * 0.5f;
        float halfHeight = m_box.height * 0.5f;
        float otherHalfWidth  = other->m_box.width  * 0.5f;
        float otherHalfHeight = other->m_box.height * 0.5f;

        float dx = thisCenterX - otherCenterX;
        float dy = thisCenterY - otherCenterY;

        float overlapX = (halfWidth + otherHalfWidth) - std::abs(dx);
        float overlapY = (halfHeight + otherHalfHeight) - std::abs(dy);

        if (overlapX > 0 && overlapY > 0)
        {
            if(overlapX < overlapY)
            {
                if(dx > 0)
                {
                    m_box.x += overlapX;
                    m_canMove.left = false;
                }
                else
                {
                    m_box.x -= overlapX;
                    m_canMove.right = false;
                }
            }
            else
            {
                if(dy > 0)
                {
                    m_box.y += overlapY;
                    m_canMove.up = false;
                }
                else
                {
                    m_box.y -= overlapY;
                    m_canMove.down = false;
                }
            }

            syncTransformToBox();
        }
    }

    void BoxCollider::moveFrom(CircleCollider* other)
    {
        std::cout << "push\n";
    }

    void BoxCollider::syncTransformToBox()
    {
        transform.position.x = m_box.x + m_box.width / 2.0f;
        transform.position.y = m_box.y + m_box.height / 2.0f;
    }

    void BoxCollider::setSize(int width, int height)
    {
        m_box.width = width;
        m_box.height = height;
    }

    int BoxCollider::getWidth()
    {
        return m_box.width;
    }

    int BoxCollider::getHeight()
    {
        return m_box.height;
    }

}

