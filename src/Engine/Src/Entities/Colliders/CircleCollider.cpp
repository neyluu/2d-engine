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
        Rectangle box = other->getBox();

        int px = std::max(box.x, std::min(transform.position.x, box.x + box.width));
        int py = std::max(box.y, std::min(transform.position.y, box.y + box.height));


        float distance = ( (transform.position.x - px) * (transform.position.x - px) )
                + ( (transform.position.y - py) * (transform.position.y - py));
//        int px = std::max(m_box.x, std::min(other->transform.position.x, m_box.x + m_size.x));
//        int py = std::max(m_box.y, std::min(other->transform.position.y, m_box.y + m_size.y));
//        std::cout << "px py " << px << " " << py << " dist " << distance << '\n';

        return distance < (m_radius * m_radius);
    }

    bool CircleCollider::collideWith(CircleCollider *other)
    {
        return false;

    }

    void CircleCollider::pushAway(Collider *other)
    {
        std::cout << "test\n";
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