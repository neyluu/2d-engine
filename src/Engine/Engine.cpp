#include "Engine.h"

Engine::Engine() { }

void Engine::init()
{
    m_running = true;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, Settings::WINDOW_TITLE);

//    SetWindowMonitor(1); // TODO TMP
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
    m_camera.offset = { GetScreenWidth() / 2.0, GetScreenHeight() / 2.0 };

    m_scene.update();


//    for(auto object : GameObject::g_gameObjects)
//    {
//        object->update();
//    }
//
//    for(auto object : GameObject::g_drawableObjects)
//    {
//        object->update();
//    }
//
//    GameObject::disableRequested();
}

void Engine::draw()
{
BeginDrawing();
    BeginMode2D(m_camera);

    DrawCircle(0,0,2,RED);

        ClearBackground(DARKGRAY);
        DrawText("2D ENGINE", 30, 30, 48, BLACK);

        m_scene.draw();
//        for(auto object : GameObject::g_drawableObjects)
//        {
//            object->draw();
//        }



    EndMode2D();

   DrawFPS(5, 5);

EndDrawing();
}


