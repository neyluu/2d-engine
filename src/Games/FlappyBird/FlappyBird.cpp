#include <iostream>
#include <filesystem>

#include "Engine/Core.h"
#include "Engine/Entities.h"

enum SceneType
{
    MAIN_MENU,
    GAME
};


class Player : public e2d::GameObject
{
public:
    Player()
    {
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_sprite);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_collider);

        m_sprite.setSize(100, 100);
        m_collider.setKinematic(true);
        m_collider.setSize(m_sprite.getWidth(), m_sprite.getHeight());

        updatePositions();
    }

    void update() override
    {
        float dt = GetFrameTime();

        float dy = 0;

        if(IsKeyPressed(KEY_SPACE))
        {
            velocityY =  -jumpForce;
        }

        velocityY += gravity * dt;

        if(velocityY > maxFallingSpeed)
        {
            velocityY = maxFallingSpeed;
        }

        y += velocityY * dt;
        updatePositions();
    }

    void updatePositions()
    {
        m_sprite.transform.position.x = x;
        m_sprite.transform.position.y = y;

        m_collider.transform.position.x = m_sprite.transform.position.x;
        m_collider.transform.position.y = m_sprite.transform.position.y;
    }

private:
    e2d::Sprite m_sprite {"Assets/bird.png" };
    e2d::BoxCollider m_collider { 100, 100 };

    int x = -400;
    int y = 100;
    float velocityY = 10;
    float gravity = 2000;
    float jumpForce = 575;
    float maxFallingSpeed = 300;
};


class Game : public e2d::GameObject
{
public:
    Game()
    {
        SetWindowTitle("Flappy Bird");
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_player);
    }

    void update() override
    {

    }

private:
    Player m_player { };
};


int main()
{
    e2d::SceneManager<SceneType>& sceneManager = e2d::SceneManager<SceneType>::get();

    e2d::Engine engine { sceneManager };
    engine.init();

    e2d::Scene m_gameScene {};
    e2d::SceneManager<SceneType>::get().addScene(SceneType::GAME, &m_gameScene);
    e2d::SceneManager<SceneType>::get().setScene(SceneType::GAME);

    Game game {};

    engine.run();
    engine.close();
}
