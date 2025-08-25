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

    private:
        Texture texture;
        Rectangle source;
    };
}

#endif //INC_2D_ENGINE_SPRITE_H
