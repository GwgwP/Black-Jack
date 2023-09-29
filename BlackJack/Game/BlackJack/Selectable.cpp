#include "Selectable.h"
#include "sgg/graphics.h"

Selectable::Selectable(const float posX, const float posY, const float width, const float height)
    :Scopable(posX, posY, width, height)
{}

void Selectable::setHighlight(const bool highlighted)
{
    m_highlighted = highlighted;
}

void Selectable::draw() const 
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	//highlighting... 

	SET_COLOR(br.fill_color, 1.f, 0.0f, 0.f);
	SET_COLOR(br.fill_secondary_color, 1.f, 0.0f, 0.f);

	br.fill_opacity = m_highlighted;
	br.fill_secondary_opacity = 0.0f;

	br.gradient = true;
	br.outline_opacity = 0.0f;
	
	graphics::drawDisk(m_posX, m_posY, m_width + 0.1f, br);
}