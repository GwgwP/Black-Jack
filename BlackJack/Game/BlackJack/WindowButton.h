#pragma once
#include "Button.h"
#include "sgg/graphics.h"


class WindowButton final
	:public Button
{
public:
	WindowButton(const std::string& name, float posX, float posY);
	void onClick() override;
	
	~WindowButton() {}
};