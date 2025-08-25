#include "Sprite.h"

namespace e2d
{
    Sprite::Sprite(std::string filename)
    {

        texture = LoadTexture(filename.c_str());
        SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
        source = { 0.0, 0.0, (float) texture.width, (float) texture.height };
    }

    Sprite::~Sprite()
    {
        UnloadTexture(texture);
    }

    void Sprite::draw()
    {
        float scaledTextureWidth = texture.width * transform.scale.x;
        float scaledTextureHeight = texture.height * transform.scale.y;

        Rectangle dest = {
                transform.position.x,
                transform.position.y,
                scaledTextureWidth,
                scaledTextureHeight
        };
        Vector2 origin = {
                (float) (scaledTextureWidth / 2.0),
                (float) (scaledTextureHeight / 2.0)
        };

        DrawTexturePro(texture, source, dest, origin, transform.rotation, WHITE);
    }

    void Sprite::update() { }
}
