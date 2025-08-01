#include "Engine/Engine.h"
#include "Game/Game.h"

int main()
{
    Game game {};
    Engine engine {};

    engine.init();
    engine.run();
    engine.close();
}
