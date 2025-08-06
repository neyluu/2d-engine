#include "Engine/Engine.h"
#include "Game/Game.h"

int main()
{
    SceneManager<int>& sm = SceneManager<int>::get();

    Engine engine { sm };
    engine.init();

    Game game {};

    engine.run();
    engine.close();
}
