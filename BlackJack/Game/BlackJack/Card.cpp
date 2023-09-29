#include "Card.h"


Card::Card(const Suits& s)
	:Scopable(POP_POSITION_X, POP_POSITION_Y, CARD_WIDTH, CARD_HEIGHT), m_suit(s)
{}

void Card::drawBackSide(graphics::Brush& br) const
{
    br.texture = "assets/back.png";

    graphics::drawRect(m_posX, m_posY, CARD_WIDTH, CARD_HEIGHT, br);

}

void Card::draw()const
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
   
    //back side
    if (!m_front)
    {
        drawBackSide(br);
        return;
    }

    //front side

    br.texture = "assets/frontCard.png";
    graphics::drawRect(m_posX, m_posY, CARD_WIDTH, CARD_HEIGHT, br);
    
    uint s = static_cast<uint>(m_suit);
 
    std::string suit_path = "assets/Suit" + std::to_string(s);
    br.texture = suit_path + ".png";
    graphics::drawRect(m_posX - m_width / 2 + 0.6f, m_posY - m_height / 2 + 1.1f, CORNER_SUIT_WIDTH, CORNER_SUIT_HEIGHT, br);
    graphics::drawRect(m_posX + m_width / 2 - 0.6f, m_posY + m_height / 2 - 1.1f, CORNER_SUIT_WIDTH, CORNER_SUIT_HEIGHT, br);
}

void Card::setFront(const bool front)
{
	m_front = front;
}

void Card::setPosX(const float posX)
{
	m_posX = posX;
}

void Card::setPosY(const float posY)
{
	m_posY = posY;
}

const float Card::getPosX() const
{
	return m_posX;
}

const float Card::getPosY() const
{
	return m_posY;
}