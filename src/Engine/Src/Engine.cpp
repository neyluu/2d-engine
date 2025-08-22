#include "Engine.h"

namespace e2d
{

    Engine::Engine(ISceneManager& sceneManager) : m_sceneManager(sceneManager)
    {}

    void Engine::init()
    {
        m_running = true;

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, Settings::WINDOW_TITLE);

        SetTargetFPS(Settings::TARGET_FPS);

        m_renderTexture = LoadRenderTexture(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);

        m_camera = {
                { 0.0, 0.0 },
                { 0.0, 0.0 },
                0.0,
                1.0
        };
    }

    void Engine::run()
    {
        while(m_running && !WindowShouldClose())
        {
            update();
            draw();
        }
    }

    void Engine::close()
    {
        UnloadRenderTexture(m_renderTexture);
        CloseWindow();
    }


    void Engine::update()
    {
        m_camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        m_sceneManager.update();
    }

    void Engine::draw()
    {
        BeginDrawing();
        BeginMode2D(m_camera);

        DrawCircle(0,0,2,RED);

        ClearBackground(DARKGRAY);
        DrawText("2D ENGINE", 30, 30, 48, BLACK);

        m_sceneManager.draw();

        EndMode2D();

        DrawFPS(5, 5);

        EndDrawing();
    }
}
