#ifndef INC_2D_ENGINE_SCENEMANAGER_H
#define INC_2D_ENGINE_SCENEMANAGER_H

#include <map>
#include <any>
#include <string>

#include "Scene.h"



class ISceneManager
{
public:
    virtual ~ISceneManager() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
};



template <typename T_SceneID>
class SceneManager : public ISceneManager
{
public:
    static SceneManager& get()
    {
        static SceneManager instance;
        return instance;
    }

    void update() override
    {
        if(m_currentScene) m_currentScene->update();
    }

    void draw() override
    {
        if(m_currentScene) m_currentScene->draw();
    }

    void addScene(T_SceneID id, Scene* scene)
    {
        if(m_scenes.find(id) != m_scenes.end()) return;

        m_scenes.insert(std::pair(id, scene));
    }

    void changeScene(T_SceneID id)
    {
        auto it = m_scenes.find(id);
        if(it == m_scenes.end()) return;

        m_currentScene = it->second.get();
    }

    Scene* GetCurrentScene() const
    {
        return m_currentScene;
    }
private:
    SceneManager() {}

    ~SceneManager()
    {
        m_scenes.clear();
    }

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::map<T_SceneID, std::unique_ptr<Scene>> m_scenes;
    Scene* m_currentScene = nullptr;
};


#endif //INC_2D_ENGINE_SCENEMANAGER_H
