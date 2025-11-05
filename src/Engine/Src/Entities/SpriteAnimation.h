#ifndef INC_2D_ENGINE_SPRITEANIMATION_H
#define INC_2D_ENGINE_SPRITEANIMATION_H

#include <iostream>
#include <vector>

#include "raylib.h"
#include "Drawable.h"
#include "Sprite.h"

namespace e2d
{
    class SpriteAnimation : public Drawable
    {
    public:
        SpriteAnimation(const std::string& filename, int frames);
        ~SpriteAnimation();

        void draw() override;
        void update() override;

        void setSize(int width, int height);
        int getWidth();
        int getHeight();

        float animationTime = 0; // seconds

    private:
        void loadAndSplitTexture(const std::string &filename);

        int m_frames;
        int m_currentFrame = 0;
        float m_timer = 0;

        std::vector<Texture2D> m_frameTextures;

        Vector2 m_size;
        Rectangle m_source;
    };
}

#endif
