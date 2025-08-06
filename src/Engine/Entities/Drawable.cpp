#include "Drawable.h"

void Drawable::setDepth(int depth)
{
    this->m_depth = depth;
}

int Drawable::getDepth() const
{
    return m_depth;
}

Drawable::Drawable()
{

}
