#ifndef INC_2D_ENGINE_BOXCOLLIDER_H
#define INC_2D_ENGINE_BOXCOLLIDER_H

#include <iostream>

#include "raylib.h"
#include "Collider.h"
#include "CircleCollider.h"

namespace e2d
{
    class BoxCollider : public Collider
    {
    public:
        BoxCollider() = default;
        BoxCollider(Rectangle box);

        void update() override;
        void draw() override;

        bool checkCollision(Collider* other) override;
        bool collideWith(BoxCollider* other) override;
        bool collideWith(CircleCollider* other) override;

        void pushAway(Collider* other) override;
        void moveFrom(BoxCollider* other) override;
        void moveFrom(CircleCollider* other) override;


        Rectangle getBox();
        void setBox(Rectangle box);
        void setPosition(float x, float y);
        void setPosition(Vector2 position);
        void setSize(float width, float height);
        void setSize(Vector2 size);

    private:
        Rectangle m_box { 0 };
        Vector2 m_moveVector { 0 };
    };
}

#endif //INC_2D_ENGINE_BOXCOLLIDER_H
