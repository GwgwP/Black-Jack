#include "FigureCard.h"

FigureCard::FigureCard(const Suits& s, const Ranks& r)
    : Card(s), m_rank(r)
{}

const uint FigureCard::getValueOfCard() const
{
	return uint(10);
}

void FigureCard::draw() const
{
    Card::draw();

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_front) {
		//draw ranks
		int r = static_cast<int>(m_rank);
		std::string rank_path = "assets/" + std::to_string(r);
		br.texture = rank_path + ".png";
		graphics::drawRect(m_posX - m_width / 2 + 0.6f, m_posY - m_height / 2 + 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
		graphics::drawRect(m_posX + m_width / 2 - 0.6f, m_posY + m_height / 2 - 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
	
		//draw center image 
		int s = static_cast<int>(m_suit);
		std::string path = "assets/" + std::to_string(r) + "_" +std::to_string(s);
		br.texture = path + ".png";
		graphics::drawRect(m_posX, m_posY, CENTER_FIGURE_WIDTH, CENTER_FIGURE_HEIGHT, br);
	}
}