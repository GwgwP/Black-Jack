#include "HelpButton.h"
#include "sgg/graphics.h"


HelpButton::HelpButton(const std::string& name, const float posX, const float posY, const float posXtext, const float posYtext, const float textWidth, const float textHeight)
	: Button(name, posX, posY), m_posXtext(posXtext), m_posYtext(posYtext), m_toggle(false), m_textWidth(textWidth), m_textHeight(textHeight)
{
}

void HelpButton::onClick()
{
	graphics::playSound("assets/sounds/papyrus.mp3", 0.7f);
	//if a HelpButton is clicked then the user is not allowed to click any other Selectable object
	//until clicked for second time (even amount of times in general), when selectables become clickable again
	m_enable = !m_enable;
	m_toggle = !m_toggle;	
}

void HelpButton::draw() const 
{
	Button::draw();
	if (!m_toggle) 
	{
		return;
	}

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.texture = "assets/" + m_name + ".png";
	graphics::drawRect(m_posXtext, m_posYtext, m_textWidth, m_textHeight, br);
}
