#include "Drawable.h"
#include "../Scenes/Scene.h"

void Drawable::setDepth(int depth)
{
    this->m_depth = depth;

    if(m_owner) m_owner->sortDrawables();
}

int Drawable::getDepth() const
{
    return m_depth;
}

