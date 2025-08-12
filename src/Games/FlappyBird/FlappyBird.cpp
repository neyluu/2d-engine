#include <iostream>
#include <filesystem>

#include "Engine/Core.h"
#include "Engine/Entities.h"


enum SceneType
{
    MAIN_MENU,
    GAME
};


class Player : public GameObject
{
public:
    Player(Scene* scene)
    {
        m_owner = scene;
        m_owner->addObject(&m_sprite);

        m_sprite.setScale(0.1);
        m_sprite.setX(m_positionX);
    }

    void update() override
    {
//        float dt = GetFrameTime();
//
//        if(IsKeyPressed(KEY_SPACE)) m_positionY -= 5000 * dt;
//
//        m_sprite.setPosition(m_positionX, m_positionY);
//
//        m_positionY += 100 * dt;
    }

private:
    Sprite m_sprite {"Assets/bird.png" };

    int m_positionX = -400;
    int m_positionY = 0;
};


class Game
{
public:
    Game()
    {
        SetWindowTitle("Flappy Bird");
        SceneManager<SceneType>::get().addScene(SceneType::GAME, &m_gameScene);
        SceneManager<SceneType>::get().setScene(SceneType::GAME);
        m_gameScene.addObject(&m_player);
    }

private:
    Scene m_gameScene {};
    Player m_player { &m_gameScene };
};


int main()
{
    SceneManager<SceneType>& sceneManager = SceneManager<SceneType>::get();

    Engine engine { sceneManager };
    engine.init();

    Game game {};

    engine.run();
    engine.close();
}
