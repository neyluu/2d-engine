#include <iostream>
#include <filesystem>

#include "Engine/Core.h"
#include "Engine/Entities.h"

using namespace e2d;

enum SceneType
{
    MAIN_MENU,
    GAME
};


class Player : public e2d::GameObject
{
public:
    Player(Scene* scene)
    {
        m_owner = scene;
        m_owner->addObject(&m_sprite);


        m_sprite.transform.scale.x = 0.1;
        m_sprite.transform.scale.y = 0.1;

        m_sprite.transform.position.x = m_positionX;
        m_sprite.transform.position.y = 100;

        m_sprite.transform.rotation = 33;

//        m_sprite.setScale(0.1);
//        m_sprite.setScale(0.1, 1);
//        m_sprite.setX(m_positionX);

    }

    void update() override
    {
        float dt = GetFrameTime();

//        if(IsKeyDown(KEY_SPACE)) velocity *= -1;
//
//        m_positionY += (100 * velocity) * dt;
//
//        m_sprite.setPosition(m_positionX, m_positionY);
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

        m_gameScene.addObject(&mov1);
        m_gameScene.addObject(&mov2);
//
        m_gameScene.addObject(&col2);
        m_gameScene.addObject(&col3);
//        m_gameScene.addObject(&col4);
//
        mov1.setKinematic(true);
        mov2.setKinematic(true);
        col4.setKinematic(true);
//
        mov1.transform.position.x = -200;
        mov1.transform.position.y = -200;

        mov2.transform.position.x = 500;
        mov2.transform.position.y = 300;

        col2.transform.position.x = 0;
        col2.transform.position.y = 0;
        col2.transform.scale.x = 1.5;

        col3.transform.position.x = 125;
        col3.transform.position.y = 125;
        col3.transform.scale.y = 0.5;

        mov1.setOnCollideEnter([]{std::cout << "Enter\n";});
        mov1.setOnCollide([]{std::cout << "Collide!\n";});
        mov1.setOnCollideExit([]{std::cout << "Exit!\n";});
//
//        mov2.setOnCollideEnter([]{std::cout << "Enter\n";});
//        mov2.setOnCollide([]{std::cout << "Collide!\n";});
//        mov2.setOnCollideExit([]{std::cout << "Exit!\n";});
//
//        mov1.setOnCollideEnter([]{std::cout << "Enter222\n";}, col4);
//        mov1.setOnCollide([]{std::cout << "Collide!222\n";}, col4);
//        mov1.setOnCollideExit([]{std::cout << "Exit!222\n";}, col4);
//
//
//        col3.transform.position.x = 350;
//        col3.transform.position.y = 200;
//
//
//
//
//
//
//
        mov1.m_isVisible = true;
        mov2.m_isVisible = true;
        col2.m_isVisible = true;
        col3.m_isVisible = true;
        col4.m_isVisible = true;
    }

    void update() override
    {
        handleMovingMov1();
        handleMovingMov2();
//        col2.transform.position.x -= 1000 * GetFrameTime();
    }

    void handleMovingMov1()
    {
//        mov1.transform.scale.x += 0.01;

        int dx = 0;
        int dy = 0;
        float dt = GetFrameTime();

//        Rectangle rect = mov1.getBox();

        int x = mov1.transform.position.x;
        int y = mov1.transform.position.y;


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

        mov1.transform.position.x = x;
        mov1.transform.position.y = y;
    }

    void handleMovingMov2()
    {
        int dx = 0;
        int dy = 0;
        float dt = GetFrameTime();

        int x = mov2.transform.position.x;
        int y = mov2.transform.position.y;


        float change = speed * dt;

        if(IsKeyDown(KEY_UP))
        {
            dy -= change;
        }
        if(IsKeyDown(KEY_RIGHT))
        {
            dx += change;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            dy += change;
        }
        if(IsKeyDown(KEY_LEFT))
        {
            dx -= change;
        }

        x += dx;
        y += dy;
//        std::cout << dx << " " << dy << "\n";

        mov2.transform.position.x = x;
        mov2.transform.position.y = y;
    }
private:
//    int colX = -200;
//    int colY = 80;
    float speed = 500;

    Scene m_gameScene {};
    Player m_player { &m_gameScene };

//    BoxCollider col { 100, 100 };

    BoxCollider mov1 { 100, 100 };
    BoxCollider mov2 { 100, 100 };
//
    BoxCollider col2 { 150, 150 };
    BoxCollider col3 { 100, 100 };
//
    BoxCollider col4 { 420, 69 };


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
