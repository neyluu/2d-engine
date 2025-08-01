#include "Engine.h"

Engine::Engine() { }

void Engine::init()
{
    m_running = true;

    InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, Settings::WINDOW_TITLE);
    SetTargetFPS(Settings::TARGET_FPS);

    m_renderTexture = LoadRenderTexture(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
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
    for(auto object : GameObject::g_gameObjects)
    {
        object->update();
    }

    GameObject::disableRequested();
}

void Engine::draw()
{
BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("2D ENGINE", 30, 30, 48, BLACK);

    for(auto object : GameObject::g_gameObjects)
    {
        object->draw();
    }


    DrawFPS(5, 5);

EndDrawing();
}

