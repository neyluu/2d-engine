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

        m_gameScene.addObject(&mov1);
        m_gameScene.addObject(&mov2);

        m_gameScene.addObject(&col2);
        m_gameScene.addObject(&col3);
        m_gameScene.addObject(&col4);

        mov1.setKinematic(true);
        mov2.setKinematic(true);
        col4.setKinematic(true);

        mov1.setOnCollideEnter([]{std::cout << "Enter\n";});
        mov1.setOnCollide([]{std::cout << "Collide!\n";});
        mov1.setOnCollideExit([]{std::cout << "Exit!\n";});

        mov1.setOnCollideEnter([]{std::cout << "Enter222\n";}, col4);
        mov1.setOnCollide([]{std::cout << "Collide!222\n";}, col4);
        mov1.setOnCollideExit([]{std::cout << "Exit!222\n";}, col4);

//        mov1.setOnCollide([]
//                          { std::cout << "Collide!\n"; });

//        mov1.setOnCollideEnter([]
//                               {
//                                   std::cout << "1 collides with 2!\n";
//                               }, mov2);


        //        mov2.setOnCollide([] {
//            std::cout << "2 collides with 1!\n";
//        }, mov1);








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
    }

    void handleMovingMov1()
    {
        int dx = 0;
        int dy = 0;
        float dt = GetFrameTime();

        Rectangle rect = mov1.getBox();

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

        mov1.setPosition(x, y);
    }

    void handleMovingMov2()
    {
        int dx = 0;
        int dy = 0;
        float dt = GetFrameTime();

        Rectangle rect = mov2.getBox();

        int x = rect.x;
        int y = rect.y;


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

        mov2.setPosition(x, y);
    }
private:
//    int colX = -200;
//    int colY = 80;
    float speed = 200;

    Scene m_gameScene {};
    Player m_player { &m_gameScene };
    BoxCollider mov1 {Rectangle {-200, 80, 100, 100} };
    BoxCollider mov2 {Rectangle {-200, -200, 100, 100} };

    BoxCollider col2 { Rectangle {0, 0, 150, 150} };
    BoxCollider col3 { Rectangle {-50, -50, 100, 100} };

    BoxCollider col4 { Rectangle {-200, 200, 420, 69} };


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
