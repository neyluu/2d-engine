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
        float dt = GetFrameTime();

        if(IsKeyDown(KEY_SPACE)) velocity *= -1;

        m_positionY += (100 * velocity) * dt;

        m_sprite.setPosition(m_positionX, m_positionY);
    }

private:
    Sprite m_sprite {"Assets/bird.png" };

    int m_positionX = -400;
    int m_positionY = 0;

    float velocity = 1;
};


class Game : GameObject
{
public:
    Game()
    {
        SetWindowTitle("Flappy Bird");
        SceneManager<SceneType>::get().addScene(SceneType::GAME, &m_gameScene);
        SceneManager<SceneType>::get().setScene(SceneType::GAME);
        m_gameScene.addObject(this);
        m_gameScene.addObject(&m_player);
        m_gameScene.addObject(&col);
        m_gameScene.addObject(&col2);
        m_gameScene.addObject(&col3);

        col.m_isKinematic = true;

        col.m_isVisible = true;
        col2.m_isVisible = true;
        col3.m_isVisible = true;
    }

    void update() override
    {
        int dx = 0;
        int dy = 0;
        float dt = GetFrameTime();

        Rectangle rect = col.getBox();

        int x = rect.x;
        int y = rect.y;


        float change = speed * dt;

        if(IsKeyDown(KEY_W))
        {
            dy -= change;
        }
        if(IsKeyDown(KEY_D))
        {
            dx += change;
        }
        if(IsKeyDown(KEY_S))
        {
            dy += change;
        }
        if(IsKeyDown(KEY_A))
        {
            dx -= change;
        }

        x += dx;
        y += dy;
//        std::cout << dx << " " << dy << "\n";

        col.setPosition(x, y);
    }

private:
//    int colX = -200;
//    int colY = 80;
    float speed = 200;

    Scene m_gameScene {};
    Player m_player { &m_gameScene };
    BoxCollider col { Rectangle {-200, 80, 200, 200} };
    BoxCollider col2 { Rectangle {0, 0, 150, 150} };
    BoxCollider col3 { Rectangle {-50, -50, 100, 100} };


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
