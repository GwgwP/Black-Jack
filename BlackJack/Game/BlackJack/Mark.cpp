#include "Mark.h"
#include "sgg/graphics.h"

Mark::Mark(const float posX, const float posY, const float radius, const uint value)
	:Selectable(posX, posY, radius, 0.0f), m_value(value)
{}

const uint Mark::getValue() const
{
	return m_value;
}

void Mark::draw() const
{
	//highlight...
	Selectable::draw();
	
	//mark...
	graphics::Brush br;

	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 1.0f;

	std::string path = "assets/Mark" + std::to_string(m_value);
	br.texture = path + ".png";
	graphics::drawRect(m_posX, m_posY, m_width, m_width, br);
	
	//selected mark...
	if (m_active)
	{
		graphics::setOrientation(graphics::getGlobalTime());
		br.texture = "assets/lightning.png"; 
		graphics::drawRect(m_posX, m_posY, m_width + 1.0f, m_width + 1.0f, br);
		graphics::resetPose();
	}
}

const bool Mark::inScope(const float x, const float y) const
{
	float dx = m_posX - x;
	float dy = m_posY - y;
	float distance = sqrtf(dx * dx + dy * dy);
	return distance < m_width / 2;
}

void Mark::onClick()
{
	graphics::playSound("assets/sounds/spin.mp3", 0.7f);
}

void Mark::setActive(const bool active)
{
	m_active = active;
}