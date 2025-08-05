#include "Engine/Engine.h"
#include "Game/Game.h"

int main()
{
    Engine engine {};
    engine.init();

    Game game {};

    engine.run();
    engine.close();
}
