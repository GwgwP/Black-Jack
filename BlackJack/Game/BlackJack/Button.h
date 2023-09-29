#pragma once
#include "Selectable.h"
#include "defines.h"

class Button :
    public Selectable
{
protected:
    const std::string m_name;

public:
    Button(const std::string& name, float posX, float posY);
    void draw()const;
    virtual void onClick() override = 0  ;

    virtual ~Button() {  };
};