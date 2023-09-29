#pragma once
#include "Button.h"
#include "Game.h"
#include "defines.h"

class GameButton final :
    public Button
{
private:
    const int m_switch_state;

public:
    GameButton(const std::string& name, const float posX, const float posY, const int switch_state);
    void onClick() override;
    ~GameButton() {};
};