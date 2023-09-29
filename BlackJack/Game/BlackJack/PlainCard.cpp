#include "PlainCard.h"
#include "defines.h" 
#include <string>


PlainCard::PlainCard(const Suits& s, const Ranks& r)
    : Card(s), m_rank(r)
{}

const uint PlainCard::getValueOfCard() const
{
    return static_cast<int>(m_rank);
}

void PlainCard::draw() const
{
    Card::draw();

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
   
    if (m_front)
    {
        int r = static_cast<int>(m_rank);
        std::string rank_path = "assets/" + std::to_string(r);
        br.texture = rank_path + ".png";
        graphics::drawRect(m_posX - m_width / 2 + 0.6f, m_posY - m_height / 2 + 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
        graphics::drawRect(m_posX + m_width / 2 - 0.6f, m_posY + m_height / 2 - 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
   
        int s = static_cast<int>(m_suit);
        std::string suit_path = "assets/Suit" + std::to_string(s);
        br.texture = suit_path + ".png";
        graphics::drawRect(m_posX, m_posY, CENTER_SUIT_WIDTH, CENTER_SUIT_HEIGHT, br);
    }
    
}
