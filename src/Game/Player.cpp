#include "Player.h"

void Player::update()
{
    float dt = GetFrameTime();

    if(IsKeyDown(KEY_D))
        x += movementSpeed * dt;
    if(IsKeyDown(KEY_S))
        y += movementSpeed * dt;
    if(IsKeyDown(KEY_A))
        x -= movementSpeed * dt;
    if(IsKeyDown(KEY_W))
        y -= movementSpeed * dt;

//    sprite.setPosition(x, y);
}

Player::Player(Scene *owner) : GameObject(owner)
{

}

