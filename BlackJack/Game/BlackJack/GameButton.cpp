#include "GameButton.h"
#include "sgg/graphics.h"

GameButton::GameButton(const std::string& name, const float posX, const float posY, const int switch_state)
	:Button(name, posX, posY), m_switch_state(switch_state)
{}

void GameButton::onClick()
{
	if (!m_enable)
	{
		graphics::playSound("assets/sounds/error.mp3", 0.3f);
		return;
	}

	graphics::playSound("assets/sounds/button.mp3", 0.7f);
	if (m_switch_state < Game::gameStates::_size)	//switch state as long as the state code provided is valid
	{
		Game::getInstance()->setState(static_cast<Game::gameStates>(m_switch_state));
	}
}