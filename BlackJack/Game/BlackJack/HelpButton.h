#pragma once
#include "Button.h"

class HelpButton final 
    :public Button
{
private:
    bool m_toggle;
    const float m_posXtext;
    const float m_posYtext;
    const float m_textWidth;
    const float m_textHeight;

public:
    HelpButton(const std::string& name, const float posX, const float posY, const float posXtext, const float posYtext, const float textWidth, const float textHeight);//????????????????????????????????
    void onClick() override;
    void draw() const override;
    
    ~HelpButton(){}
};

