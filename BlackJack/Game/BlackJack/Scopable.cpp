#include "Scopable.h"

Scopable::Scopable(const float posX, const float posY, const float width, const float height)
    :m_posX(posX), m_posY(posY), m_width(width), m_height(height)
{}

bool Scopable::m_enable = true;

const bool Scopable::inScope(const float x, const float y) const
{
    return ((abs(x - m_posX) < m_width / 2) && (abs(y - m_posY) < m_height / 2));
}

const bool Scopable::enableSignal()
{
    return m_enable;
}