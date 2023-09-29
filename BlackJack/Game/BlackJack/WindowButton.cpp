#include "WindowButton.h"

WindowButton::WindowButton(const std::string& name, float posX, float posY)
	:Button(name, posX, posY)
{}

void WindowButton::onClick()
{
	graphics::stopMessageLoop();
}
