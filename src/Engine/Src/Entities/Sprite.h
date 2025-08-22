#ifndef INC_2D_ENGINE_SPRITE_H
#define INC_2D_ENGINE_SPRITE_H

#include <iostream>

#include "raylib.h"
#include "Drawable.h"
#include "../Scenes/Scene.h"

namespace e2d
{
    class Sprite : public Drawable
    {
    public:
        Sprite(std::string filename);
        ~Sprite();

        void draw() override;
        void update() override;

        void setX(int x);
        void setY(int y);
        void setPosition(int x, int y);
        void setScale(float scale);
        void setScale(float scaleX, float scaleY);
        void setScaleX(float scaleX);
        void setScaleY(float scaleY);
        void setRotation(float rotation);

    private:
        Texture texture;
        Rectangle source;
        int x = 0;
        int y = 0;
        Vector2 scale { 1, 1 };
        float rotation = 0;
    };
}

#endif //INC_2D_ENGINE_SPRITE_H
