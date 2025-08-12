#include "Game.h"

#include "../Engine/Scenes/SceneManager.h"

Game::Game()
{
    SceneManager<std::string>::get().addScene("main", &scene);
    SceneManager<std::string>::get().changeScene("main");
//    SceneManager<std::string>::get().changeScene("main");

    scene.addObject(&sprite);
    scene.addObject(&sprite2);


    sprite.setDepth(100);
//    sprite.setPosition(-300, 0);


    scene2.addObject(&sprite2);
    SceneManager<std::string>::get().addScene("2", &scene2);
    SceneManager<std::string>::get().changeScene("2");
    SceneManager<std::string>::get().changeScene("main");
}
