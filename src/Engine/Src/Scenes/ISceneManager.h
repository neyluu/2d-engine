#ifndef INC_2D_ENGINE_ISCENEMANAGER_H
#define INC_2D_ENGINE_ISCENEMANAGER_H

namespace e2d
{
    class ISceneManager
    {
    public:
        virtual ~ISceneManager() = default;
        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif //INC_2D_ENGINE_ISCENEMANAGER_H
