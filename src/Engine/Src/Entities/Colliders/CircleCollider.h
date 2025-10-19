#ifndef INC_2D_ENGINE_CIRCLECOLLIDER_H
#define INC_2D_ENGINE_CIRCLECOLLIDER_H

#include "Collider.h"

namespace e2d
{
    class CircleCollider : public Collider
    {
    public:
        CircleCollider() = default;
        CircleCollider(int radius);

        void update() override;
        void draw() override;

        bool checkCollision(Collider* other) override;
        bool collideWith(BoxCollider* other) override;
        bool collideWith(CircleCollider* other) override;

        void pushAway(Collider* other) override;
        void moveFrom(BoxCollider* other) override;
        void moveFrom(CircleCollider* other) override;

        void setRadius(int radius);
        int getRadius();

    private:
        int m_radius { 0 };
    };
}


#endif //INC_2D_ENGINE_CIRCLECOLLIDER_H
