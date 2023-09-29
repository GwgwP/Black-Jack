#include "Level.h"
#include "sgg/graphics.h"


uint Level::numOfLevels = 0;

Level::Level(const uint cordX, const uint cordY)
	:Scopable((cordX + 0.5f)* (SQUARE_SIZE), (cordY + 0.73f)* (SQUARE_SIZE), ROCK_WIDTH, ROCK_HEIGHT),
    m_cordX(cordX), m_cordY(cordY), m_id(numOfLevels)
{
	++numOfLevels;
}

const uint Level::getId() const
{
    return m_id;
}

const uint Level::getCordX() const
{
    return m_cordX;
}

const uint Level::getCordY() const
{
    return m_cordY;
}

void Level::draw() const 
{
    graphics::Brush rck;
    rck.outline_opacity = 0.0f;
    SET_COLOR(rck.fill_color, 1.0f, 1.0f, 1.0f);

    rck.texture = "assets/rock.png";
    
    if (m_hover)
    {
        graphics::drawRect(m_posX, m_posY - 0.3f, ROCK_WIDTH, ROCK_HEIGHT, rck);
        rck.texture = "assets/" + std::to_string(m_id + 1) + ".png";
        graphics::drawRect(m_posX, m_posY - 0.3f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, rck);
    }
    else
    {
        graphics::drawRect(m_posX, m_posY, ROCK_WIDTH, ROCK_HEIGHT, rck);
    }
}

void Level::setHover(const bool hover)
{
    m_hover = hover;
}

void Level::reset()
{
    numOfLevels = 0;
}