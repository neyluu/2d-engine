#ifndef INC_2D_ENGINE_ENGINE_H
#define INC_2D_ENGINE_ENGINE_H

#include "raylib.h"
#include "Configs/Settings.h"
#include "Entities/GameObject.h"
#include "Entities/Drawable.h"
#include "Scenes/Scene.h"


class Engine
{
public:
    Engine();

    void init();
    void run();
    void close();

private:
    bool m_running = false;
    RenderTexture2D m_renderTexture {};
    Camera2D m_camera {};

    Scene m_scene {};

    void update();
    void draw();
};


#endif //INC_2D_ENGINE_ENGINE_H
