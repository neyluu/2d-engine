#ifndef INC_2D_ENGINE_DRAWABLE_H
#define INC_2D_ENGINE_DRAWABLE_H

#include "GameObject.h"

class Scene;

class Drawable : public GameObject
{
public:
    Drawable();

    virtual void draw() = 0;

    void setDepth(int depth);
    int getDepth() const;
private:
    int m_depth { 0 };
};


#endif //INC_2D_ENGINE_DRAWABLE_H
