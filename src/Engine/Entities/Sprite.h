#ifndef INC_2D_ENGINE_SPRITE_H
#define INC_2D_ENGINE_SPRITE_H

#include <iostream>

#include "raylib.h"
#include "GameObject.h"

class Sprite : public GameObject
{
public:
    Sprite(int x, int y);

    void draw() override;
    void update() override;

    int x = 0;
    int y = 0;
};


#endif //INC_2D_ENGINE_SPRITE_H
