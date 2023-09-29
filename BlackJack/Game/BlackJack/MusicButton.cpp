#include "MusicButton.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "Game.h"

MusicButton::MusicButton(float posX, float posY)
	:Button("", posX, posY)
{}
bool MusicButton::m_music = true;

void MusicButton::draw() const
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 1.0f;

	std::string path;

	if (m_music)
	{
		path = "assets/musicOn.png";
	}
	else
	{
		path = "assets/musicOff.png";
	}
	
	br.texture = path;
	graphics::drawRect(m_posX, m_posY, MUSIC_BUTTON, MUSIC_BUTTON, br);
}

void MusicButton::onClick()
{
	m_music = !m_music; 

	Game::getInstance()->setVolume(m_music);
}

const bool MusicButton::inScope(const float x, const float y) const
{
	float dx = m_posX - x;
	float dy = m_posY - y;
	float distance = sqrtf(dx * dx + dy * dy);
	return distance < m_width / 2;
}
