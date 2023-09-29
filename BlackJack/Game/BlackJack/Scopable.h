#pragma once
#include "defines.h"

class Scopable
{
protected:
	float m_posX;
	float m_posY;
	const float m_width;
	const float m_height;
	
	static bool m_enable;	

public:
	Scopable(const float posX, const float posY, const float width, const float height);
	const virtual bool inScope(const float x, const float y) const;
	virtual void draw() const = 0;
	const static bool enableSignal();	
	
	virtual ~Scopable() {};
};