#include "Sprite.h"

namespace e2d
{
    Sprite::Sprite(std::string filename)
    {

        m_texture = LoadTexture(filename.c_str());
        SetTextureWrap(m_texture, TEXTURE_WRAP_CLAMP);
        m_source = {0.0, 0.0, (float) m_texture.width, (float) m_texture.height };

        m_size.x = m_texture.width;
        m_size.y = m_texture.height;
    }

    Sprite::~Sprite()
    {
        UnloadTexture(m_texture);
    }

    void Sprite::draw()
    {
        float scaledTextureWidth = m_size.x * transform.scale.x;
        float scaledTextureHeight = m_size.y * transform.scale.y;

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

        DrawTexturePro(m_texture, m_source, dest, origin, transform.rotation, WHITE);
    }

    void Sprite::update() { }

    void Sprite::setSize(int width, int height)
    {
        m_size.x = width;
        m_size.y = height;
    }

    int Sprite::getWidth()
    {
        return m_size.x;
    }

    int Sprite::getHeight()
    {
        return m_size.y;
    }

}
