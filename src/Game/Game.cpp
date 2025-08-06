#include "Game.h"

#include "../Engine/Scenes/SceneManager.h"

Game::Game()
{
    SceneManager<int>::get().addScene(1, &scene);
    SceneManager<int>::get().changeScene(1);

    scene.addObject(&sprite);
    scene.addObject(&sprite2);

    sprite.setPosition(-300, 0);
}
