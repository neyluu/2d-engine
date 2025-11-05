#include <iostream>
#include <filesystem>

#include "Engine/Core.h"
#include "Engine/Entities.h"

enum SceneType
{
    MAIN_MENU,
    GAME
};

class Pipes : public e2d::GameObject
{
public:
    Pipes()
    {
        transform.position.x = 100;
        transform.position.y = 100;

        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_top);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_bottom);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_coin);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_colliderTop);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_colliderBottom);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_trigger);

        {
            m_top.setDepth(-2);
            m_top.transform.rotation = 180;
            m_bottom.setDepth(-2);

            m_colliderTop.setDepth(1000);
            m_colliderBottom.setDepth(1000);

            m_colliderTop.setSize(m_top.getWidth(), m_top.getHeight());
            m_colliderBottom.setSize(m_bottom.getWidth(), m_bottom.getHeight());
        }
        {
            m_coin.transform.scale.x = 2;
            m_coin.transform.scale.y = 2;
            m_coin.setDepth(-3);

//            m_trigger.isVisible = true;
            m_trigger.setKinematic(false);
            m_trigger.setTrigger(true);
        }

        updatePositions();
    }

    void update() override
    {
        if(isGameOver) return;

        transform.position.x -= 100 * GetFrameTime();

        updatePositions();
    }

    void updatePositions()
    {
        m_top.transform.position.y = transform.position.y - 200 - pipesOffset;
        m_bottom.transform.position.y = transform.position.y + 200 + pipesOffset;

        m_top.transform.position.x = transform.position.x;
        m_bottom.transform.position.x = transform.position.x;


        m_colliderTop.transform.position.x = transform.position.x;
        m_colliderTop.transform.position.y = transform.position.y - 200 - pipesOffset;

        m_colliderBottom.transform.position.x = transform.position.x;
        m_colliderBottom.transform.position.y = transform.position.y + 200 + pipesOffset;

        m_coin.transform.position.x = transform.position.x;
        m_coin.transform.position.y = transform.position.y;

        m_trigger.transform.position.x = transform.position.x;
        m_trigger.transform.position.y = transform.position.y;
    }

    void disableCoin()
    {
        m_coin.disable();
        m_trigger.disable();
    }

    void gameOver()
    {
        isGameOver = true;
    }

private:
    e2d::Sprite m_top { "Assets/pipe-green.png" };
    e2d::Sprite m_bottom { "Assets/pipe-green.png" };
    e2d::Sprite m_coin { "Assets/coin.png" };
    e2d::BoxCollider m_colliderTop { 10, 10};
    e2d::BoxCollider m_colliderBottom { 10, 10};
    e2d::CircleCollider m_trigger { 35 };

    int pipesOffset = 100;
    bool isGameOver = false;

    friend class PipesGenerator;
};


class Player;

class PipesGenerator : public e2d::GameObject
{
public:
    PipesGenerator(const e2d::Collider &playerCollider, std::function<void()> onCollide, std::function<void()> onTrigger)
        : playerCollider(playerCollider), onCollide(onCollide), onTrigger(onTrigger)
    {
        generateNewPipes();
    }

    ~PipesGenerator()
    {
        for(Pipes* pipes : allPipes)
        {
            delete pipes;
        }
    }

    void update() override
    {
        if(isGameOver) return;

        counter += GetFrameTime();
        if(counter > generationTime)
        {
            generateNewPipes();
            counter = 0;
        }
    }

    void generateNewPipes()
    {
        Pipes* pipes = new Pipes;
        allPipes.push_back(pipes);

        pipes->transform.position.x = e2d::Settings::WINDOW_WIDTH / 2 + 50;
        pipes->transform.position.y = GetRandomValue(-200, 200);

        pipes->m_colliderTop.setOnCollide(onCollide, playerCollider);
        pipes->m_colliderBottom.setOnCollide(onCollide, playerCollider);
        pipes->m_trigger.setOnCollideEnter(
            [this, pipes]
            {
                pipes->disableCoin();
                onTrigger();
            },
            playerCollider);

        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(pipes);
    }

    void gameOver()
    {
        isGameOver = true;

        for(Pipes* pipes : allPipes)
        {
            pipes->gameOver();
        }
    }

private:
    const e2d::Collider& playerCollider;
    std::function<void()> onCollide;
    std::function<void()> onTrigger;

    float counter = 0;
    float generationTime = 3;
    bool isGameOver = false;

    std::vector<Pipes*> allPipes {};
};


class Player : public e2d::GameObject
{
public:
    Player()
    {
        this->transform.position.x = -400;
        this->transform.position.y = 100;

        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_sprite);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_collider);

        m_sprite.animationTime = 0.4;
        m_sprite.setSize(100, 100);
        m_sprite.setDepth(-2);

//        m_collider.isVisible = true;
        m_collider.setKinematic(true);
        m_collider.setDepth(-1);

        updatePositions();
    }

    void update() override
    {
        if(isGameOver) return;

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

        transform.position.y += velocityY * dt;
        updatePositions();
    }

    void updatePositions()
    {
        m_sprite.transform.position.x = transform.position.x;
        m_sprite.transform.position.y = transform.position.y;

        m_collider.transform.position.x = m_sprite.transform.position.x;
        m_collider.transform.position.y = m_sprite.transform.position.y;
    }

    void gameOver()
    {
        isGameOver = true;
    }

    e2d::CircleCollider m_collider { 30 };

private:
    e2d::SpriteAnimation m_sprite { "Assets/birdAnimations/birdHorizontal.png", 4 };

    float velocityY = 10;
    float gravity = 2000;
    float jumpForce = 575;
    float maxFallingSpeed = 300;
    bool isGameOver = false;
};


class Game : public e2d::Drawable
{
public:
    Game()
    {
        SetWindowTitle("Flappy Bird");
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(this);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_player);
        e2d::SceneManager<SceneType>::get().getCurrentScene()->addObject(&m_pipesGenerator);

//        m_player.m_collider.setOnCollideEnter([this]{ gameOver(); });
    }

    void update() override
    {

    }

    void draw() override
    {
        std::string points = "Points: " + std::to_string(m_points);
        const char * points_c = points.c_str();
        int textLen = (int) MeasureText(points_c, m_pointsFontsSize);
        DrawText(points_c, -(textLen / 2), -300, m_pointsFontsSize, WHITE);
    }

    void gameOver()
    {
        std::cout << "Game over!\n";
        m_player.gameOver();
        m_pipesGenerator.gameOver();
    }

    void addPoint()
    {
        m_points++;
        std::cout << "Points: " << m_points << "\n";
    }

private:
    Player m_player {};
    PipesGenerator m_pipesGenerator {
        m_player.m_collider,
        [this]{ gameOver(); },
        [this]{ addPoint(); }
    };

    int m_points = 0;

    int m_pointsFontsSize = 48;
    Color m_pointsFontColor = WHITE;
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
