#ifndef INC_2D_ENGINE_TRANSFORM_H
#define INC_2D_ENGINE_TRANSFORM_H

#include "raylib.h"

namespace e2d
{
    struct Transform
    {
        Vector2 position { 0, 0 };
        Vector2 size { 0, 0 };
        Vector2 scale { 1, 1 };
        float rotation { 0 };
    };
}


#endif //INC_2D_ENGINE_TRANSFORM_H
