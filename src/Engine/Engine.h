#ifndef INC_2D_ENGINE_ENGINE_H
#define INC_2D_ENGINE_ENGINE_H

#include <any>

#include "raylib.h"
#include "Configs/Settings.h"
#include "Entities/GameObject.h"
#include "Entities/Drawable.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"


class Engine
{
public:
    Engine(ISceneManager& sceneManager);

    void init();
    void run();
    void close();

private:
    void update();
    void draw();

    bool m_running = false;
    RenderTexture2D m_renderTexture {};
    Camera2D m_camera {};

    ISceneManager& m_sceneManager;
};


#endif //INC_2D_ENGINE_ENGINE_H
