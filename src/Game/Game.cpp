#include <functional>
#include <random>
#include "Game.h"

Game::Game()
{
    Sprite s5 {300, 300};
    std::cout << "test\n";

    for(int i = 0; i < 1000; i++)
    {
        Sprite* sprite = new Sprite {600,500};
//        bool randBool = GetRandomValue(0, 1);

//        if(randBool) sprite->enable();
//        else         sprite->disable();

        m_sprites.push_back(sprite);
    }
}
