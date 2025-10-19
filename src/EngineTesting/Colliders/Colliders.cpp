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
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(this);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_colBox1);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_colBox2);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_movColBox1);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_movColBox2);

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
    }
    
private:
    e2d::BoxCollider m_colBox1 { 100, 100 };
    e2d::BoxCollider m_colBox2 { 50, 150 };
    e2d::BoxCollider m_movColBox1 { 50, 50 };
    e2d::BoxCollider m_movColBox2 { 100, 200 };

    float m_movColBox1Speed = 250;
    float m_movColBox2Speed = 150;
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
