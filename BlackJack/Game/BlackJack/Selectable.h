#pragma once
#include "Scopable.h"
#include "defines.h"

class Selectable
	:public Scopable
{
protected:
	
	bool m_highlighted = false;

public:
	Selectable(const float posX, const float posY, const float width, const float height);
	void setHighlight(const bool highlighted);
	virtual void onClick() = 0;
	void draw() const ;
	
	virtual ~Selectable() {};
};

