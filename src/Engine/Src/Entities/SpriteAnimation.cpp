#include "SpriteAnimation.h"

namespace e2d
{
    SpriteAnimation::SpriteAnimation(const std::string& filename, int frames)
    {
        m_frames = frames;
        loadAndSplitTexture(filename);
    }

    SpriteAnimation::~SpriteAnimation()
    {
        for(const auto frame : m_frameTextures)
        {
            UnloadTexture(frame);
        }
    }

    void SpriteAnimation::draw()
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

        DrawTexturePro(m_frameTextures[m_currentFrame], m_source, dest, origin, transform.rotation, WHITE);
    }

    void SpriteAnimation::update()
    {
        if(animationTime <= 0)
        {
            std::cout << "ERROR: animation time cannot be smaller than 0\n";
        }

        m_timer += GetFrameTime();

        float timePerFrame = animationTime / m_frames;

        if(m_timer > timePerFrame)
        {
            m_currentFrame++;

            if(m_currentFrame >= m_frames)
            {
                m_currentFrame = 0;
            }

            m_timer = 0;
        }
    }

    void SpriteAnimation::setSize(int width, int height)
    {
        m_size.x = width;
        m_size.y = height;
    }

    int SpriteAnimation::getWidth()
    {
        return m_size.x;
    }

    int SpriteAnimation::getHeight()
    {
        return m_size.y;
    }

    void SpriteAnimation::loadAndSplitTexture(const std::string &filename)
    {
        Texture2D textureRaw = LoadTexture(filename.c_str());
        SetTextureWrap(textureRaw, TEXTURE_WRAP_CLAMP);

        m_frameTextures.reserve(m_frames);

        int rawWidth  = textureRaw.width;
        int rawHeight = textureRaw.height;

        int counter = std::max(rawWidth, rawHeight);
        int step = counter / m_frames;

        bool horizontal = rawWidth > rawHeight;
        float frameWidth  = horizontal ? step : rawWidth;
        float frameHeight = horizontal ? rawHeight : step;

        m_source = { 0, 0, frameWidth, frameHeight };
        m_size.x = frameWidth;
        m_size.y = frameHeight;

        for(int i = 0; i < m_frames; i++)
        {
            Image image = LoadImageFromTexture(textureRaw);
            float x = horizontal ? (i * step) : 0;
            float y = horizontal ? 0 : (i * step);

            Rectangle crop = { x, y, frameWidth, frameHeight };
            ImageCrop(&image, crop);
            Texture2D frame = LoadTextureFromImage(image);

            UnloadImage(image);
            m_frameTextures.push_back(frame);
        }

        UnloadTexture(textureRaw);
    }
}
