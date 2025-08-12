#include <iostream>
#include <filesystem>

#include "Engine/Core.h"
#include "Engine/Entities.h"


enum SceneType
{
    MAIN_MENU,
    GAME
};

SceneManager<SceneType>& sceneManager = SceneManager<SceneType>::get();


class Player : public GameObject
{
public:
    Player(Scene* scene)
    {
        m_owner = scene;
        m_owner->addObject(&sprite);

        sprite.setScale(0.75);
    }

    void update() override
    {

    }

private:
    Sprite sprite { "Assets/bird.png" };
//    Sprite sprite { "src/Games/FlappyBird/Assets/bird.png" };
};


class Game
{
public:
    Game()
    {
        SetWindowTitle("Flappy Bird");
        sceneManager.addScene(GAME, &gameScene);
        sceneManager.changeScene(GAME);
        gameScene.addObject(&player);
    }

private:
    Scene gameScene {};
    Player player { &gameScene };
};


int main()
{
    std::cout << "main: " << std::filesystem::current_path() << "\n";

    Engine engine { sceneManager };
    engine.init();

    Game game {};

    engine.run();
    engine.close();
}
