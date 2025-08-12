#include "Sprite.h"

#include <filesystem>

Sprite::Sprite(std::string filename)
{

    std::cout << "sprite: " << std::filesystem::current_path() << "\n";
    texture = LoadTexture(filename.c_str());
    source = { 0.0, 0.0, (float) texture.width, (float) texture.height };
}

Sprite::~Sprite()
{
    UnloadTexture(texture);
}

void Sprite::draw()
{
    float scaledTextureWidth = texture.width * scale.x;
    float scaledTextureHeight = texture.height * scale.y;

    Rectangle dest = { (float) x, (float) y, scaledTextureWidth, scaledTextureHeight };
    Vector2 origin = {(float) (scaledTextureWidth / 2.0), (float) (scaledTextureHeight / 2.0)};

    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}

void Sprite::update() { }

void Sprite::setX(int x)
{
    this->x = x;
}

void Sprite::setY(int y)
{
    this->y = y;
}

void Sprite::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Sprite::setScale(float scale)
{
    setScale(scale, scale);
}

void Sprite::setScale(float scaleX, float scaleY)
{
    setScaleX(scaleX);
    setScaleY(scaleY);
}

void Sprite::setScaleX(float scaleX)
{
    scale.x = scaleX;
    texture.width = int(texture.width * scale.x);
}

void Sprite::setScaleY(float scaleY)
{
    scale.y = scaleY;
    texture.height = int(texture.height * scale.y);
}

void Sprite::setRotation(float rotation)
{
    this->rotation = rotation;
}
