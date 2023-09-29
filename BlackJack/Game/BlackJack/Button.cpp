#include "Button.h"
#include "sgg/graphics.h"


Button::Button(const std::string& name, float posX, float posY)
	:Selectable(posX, posY, BUTTON_WIDTH, BUTTON_HEIGHT), m_name(name)
{}


void Button::draw() const
{
	//highlighting
	Selectable::draw();

	//button...
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 1.0f;
	br.texture = "assets/button.png";
	graphics::drawRect(m_posX, m_posY, m_width, m_height, br);


	graphics::setFont("assets/Eastwood.ttf"); 
	SET_COLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	graphics::drawText(m_posX-m_width/2+0.2f, m_posY- m_height / 2 + 1.0f, 0.6f, m_name, br);
}