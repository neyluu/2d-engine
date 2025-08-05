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
//    Sprite s2 { &scene, "../Assets/player01.png"};
    Sprite sprite { &scene, "../Assets/player01.png"};

//    Player player;
//    Sprite s3 {"../Assets/transparent.png"};
//    Sprite s3 {"../Assets/gradient01.png"};
};


#endif //INC_2D_ENGINE_GAME_H
