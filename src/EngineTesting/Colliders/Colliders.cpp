#include <iostream>

#include "Engine/Core.h"
#include "Engine/Entities.h"

enum SceneType
{
    MAIN
};

class CollidersTest : public e2d::GameObject
{
public:
    CollidersTest()
    {
        e2d::Scene *scene = e2d::SceneManager<SceneType>::get().getCurrentScene();

        scene->addObject(this);
        scene->addObject(&m_colBox1);
        scene->addObject(&m_colBox2);
        scene->addObject(&m_movColBox1);
        scene->addObject(&m_movColBox2);
        scene->addObject(&m_cirCol1);
        scene->addObject(&m_movCir1);

        m_colBox1.m_isVisible = true;

        m_colBox2.m_isVisible = true;
        m_colBox2.transform.position.x = -200;
        m_colBox2.transform.position.y = -200;

        m_movColBox1.m_isVisible = true;
        m_movColBox1.setKinematic(true);
        m_movColBox1.transform.position.x = -300;
        m_movColBox1.transform.position.y = -300;

        m_movColBox2.m_isVisible = true;
        m_movColBox2.setKinematic(true);
        m_movColBox2.transform.position.x = 300;
        m_movColBox2.transform.position.y = 300;

        m_cirCol1.m_isVisible = true;
        m_cirCol1.transform.position.x = -100;
        m_cirCol1.transform.position.y = -100;

        m_movCir1.m_isVisible = true;
        m_movCir1.setKinematic(true);
        m_cirCol1.transform.position.x = 0;
        m_movCir1.transform.position.y = 300;
    }

    void update() override
    {

        float dt = GetFrameTime();

        if(IsKeyDown(KEY_W))
        {
            m_movColBox1.transform.position.y -= m_movColBox1Speed * dt;
        }
        if(IsKeyDown(KEY_D))
        {
            m_movColBox1.transform.position.x += m_movColBox1Speed * dt;
        }
        if(IsKeyDown(KEY_S))
        {
            m_movColBox1.transform.position.y += m_movColBox1Speed * dt;
        }
        if(IsKeyDown(KEY_A))
        {
            m_movColBox1.transform.position.x -= m_movColBox1Speed * dt;
        }

        
        if(IsKeyDown(KEY_UP))
        {
            m_movColBox2.transform.position.y -= m_movColBox2Speed * dt;
        }
        if(IsKeyDown(KEY_RIGHT))
        {
            m_movColBox2.transform.position.x += m_movColBox2Speed * dt;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            m_movColBox2.transform.position.y += m_movColBox2Speed * dt;
        }
        if(IsKeyDown(KEY_LEFT))
        {
            m_movColBox2.transform.position.x -= m_movColBox2Speed * dt;
        }


        if(IsKeyDown(KEY_U))
        {
            m_movCir1.transform.position.y -= m_movCir1Speed * dt;
        }
        if(IsKeyDown(KEY_K))
        {
            m_movCir1.transform.position.x += m_movCir1Speed * dt;
        }
        if(IsKeyDown(KEY_J))
        {
            m_movCir1.transform.position.y += m_movCir1Speed * dt;
        }
        if(IsKeyDown(KEY_H))
        {
            m_movCir1.transform.position.x -= m_movCir1Speed * dt;
        }

    }
    
private:
    e2d::BoxCollider m_colBox1 { 100, 100 };
    e2d::BoxCollider m_colBox2 { 50, 150 };
    e2d::BoxCollider m_movColBox1 { 50, 50 };
    e2d::BoxCollider m_movColBox2 { 100, 75 };

    e2d::CircleCollider m_cirCol1 { 50 };
    e2d::CircleCollider m_movCir1 { 50 };

    float m_movColBox1Speed = 250;
    float m_movColBox2Speed = 150;
    float m_movCir1Speed = 150;


};

int main()
{
    e2d::SceneManager<SceneType>& sceneManager = e2d::SceneManager<SceneType>::get();

    e2d::Engine engine { sceneManager };

    engine.init();

    e2d::Scene mainScene {};
    sceneManager.addScene(MAIN, &mainScene);
    sceneManager.setScene(MAIN);

    CollidersTest collidersTest {};

    engine.run();
    engine.close();
}
