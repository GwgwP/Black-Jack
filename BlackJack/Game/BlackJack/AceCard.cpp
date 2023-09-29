#include "AceCard.h"
#include "defines.h"

AceCard::AceCard(const Suits& s) :
	Card(s)
{}

void AceCard::setAsOne(const bool asOne)
{
	m_asOne = asOne;
};

const uint AceCard::getValueOfCard()const
{
	if (m_asOne)
		return 1;

	return 11;
}

void AceCard::draw() const
{
	Card::draw();

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_front) 
	{
		//draw ranks
		int r = static_cast<int>(m_rank);
		std::string rank_path = "assets/A";
		br.texture = rank_path + ".png";
		graphics::drawRect(m_posX - m_width / 2 + 0.6f, m_posY - m_height / 2 + 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
		graphics::drawRect(m_posX + m_width / 2 - 0.6f, m_posY + m_height / 2 - 0.5f, CORNER_RANK_WIDTH, CORNER_RANK_HEIGHT, br);
	
		//draw center image 
		int s = static_cast<int>(m_suit);
		std::string path = "assets/A_" + std::to_string(s);
		br.texture = path + ".png";
		graphics::drawRect(m_posX, m_posY, CENTER_ACE_WIDTH, CENTER_ACE_HEIGHT, br);
	}
}