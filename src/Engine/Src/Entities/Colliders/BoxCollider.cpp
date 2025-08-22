#include "BoxCollider.h"

BoxCollider::BoxCollider(Rectangle box)
{
    this->m_box = box;
}

Rectangle BoxCollider::getBox()
{
    return m_box;
}

void BoxCollider::setBox(Rectangle box)
{
    this->m_box = box;
}

void BoxCollider::update()
{
    Collider::update();
}

void BoxCollider::draw()
{
    if( ! m_isVisible) return;

    DrawRectangle(m_box.x, m_box.y, m_box.width, m_box.height, WHITE);
    DrawRectangleLinesEx(m_box, 2, RED);
}

bool BoxCollider::checkCollision(Collider* other)
{
    m_canMove.enableAll();
    return other->collideWith(this);
}

bool BoxCollider::collideWith(BoxCollider* other)
{
//    std::cout << "rect(" << m_box.x << " " << m_box.y << " " << m_box.width << " " << m_box.height  << ") rect("
//            << other->m_box.x << " " << other->m_box.y << " " << other->m_box.width << " " << other->m_box.height  << ")\n";
    return (
        m_box.x < other->m_box.x + other->m_box.width &&
        m_box.x + m_box.width > other->m_box.x &&
        m_box.y < other->m_box.y + other->m_box.height &&
        m_box.y + m_box.height > other->m_box.y
    );
}

bool BoxCollider::collideWith(CircleCollider* other)
{
    
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
    }
}

void BoxCollider::moveFrom(CircleCollider* other)
{

}


void BoxCollider::setPosition(float x, float y)
{
    if( ! m_isKinematic)
    {
        std::cout << "WARNING: Moving static collider!\n";
        return;
    }

    int oldX = m_box.x;
    int oldY = m_box.y;

    if((x < m_box.x && m_canMove.left) || (x > m_box.x && m_canMove.right)) m_box.x = x;
    if((y < m_box.y && m_canMove.up) || (y > m_box.y && m_canMove.down)) m_box.y= y;

    m_moveVector = { x - oldX, y - oldY};
}

void BoxCollider::setPosition(Vector2 position)
{
    setPosition(position.x, position.y);
}

void BoxCollider::setSize(float width, float height)
{
    if( ! m_isKinematic)
    {
        std::cout << "WARNING: Changing size of static collider!\n";
        return;
    }

    m_box.width = width;
    m_box.height = height;
}

void BoxCollider::setSize(Vector2 size)
{
    setSize(size.x, size.y);
}
