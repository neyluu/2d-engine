#ifndef INC_2D_ENGINE_GAME_H
#define INC_2D_ENGINE_GAME_H

#include "../Engine/Entities/Sprite.h"

#include <vector>

class Game
{
public:
    Game();
private:
    Sprite s1 {100, 200};
    Sprite s2 {100, 250};

    std::vector<Sprite*> m_sprites;
};


#endif //INC_2D_ENGINE_GAME_H
