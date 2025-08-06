#ifndef INC_2D_ENGINE_GAME_H
#define INC_2D_ENGINE_GAME_H

#include "../Engine/Entities/Sprite.h"
#include "../Engine/Scenes/Scene.h"

#include "Player.h"

#include <vector>

class Game
{
public:
    Game();
private:
    Scene scene {};
//    Scene scene2 {};
    Sprite sprite { "../Assets/player01.png"};
    Sprite sprite2 { "../Assets/gradient01.png"};
};


#endif //INC_2D_ENGINE_GAME_H
