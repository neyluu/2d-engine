#include "Sprite.h"
#include "../Configs/Settings.h"

Sprite::Sprite(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Sprite::draw()
{
    DrawRectangle(x, y, 10, 10, PINK);
}

void Sprite::update()
{
    int c = 1;
    int dx = GetRandomValue(-c, c);
    int dy = GetRandomValue(-c, c);
    x += dx;
    y += dy;
//
    if(x - 10 < 0 || x + 10 > Settings::WINDOW_WIDTH
    || y - 10 < 0 || y + 10 > Settings::WINDOW_HEIGHT)
    {
        requestDisable();
    }
}
