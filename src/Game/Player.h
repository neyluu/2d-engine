#ifndef INC_2D_ENGINE_PLAYER_H
#define INC_2D_ENGINE_PLAYER_H

#include "../Engine/Entities/Sprite.h"

class Player : public GameObject
{
public:
    Player();

    void update() override;
private:
//    Sprite sprite {"../Assets/player01.png"};

    int x {100};
    int y {100};
    float movementSpeed = 250;

};


#endif //INC_2D_ENGINE_PLAYER_H
