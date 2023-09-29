#pragma once
#include "Button.h"
#include "Game.h"

class MusicButton :
    public Button
{
    static bool m_music;
    
public:
    MusicButton(const float posX, const float posY);
    void draw() const override;
    
    void onClick() override;
    const bool inScope(const float x, const float y) const override;


    ~MusicButton() {};
};