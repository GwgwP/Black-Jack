#pragma once
#include "Selectable.h"
#include "defines.h"

class Mark final
	:public Selectable{

private:
	const int m_value;
	bool m_active = true;
	
public:
	Mark(const float posX, const float posY, const float radius, const uint value);
	const uint getValue() const ;
	void draw() const override;
	const bool inScope(float x, float y) const override;
	void onClick() override; 
	void setActive(const bool active);
	
	~Mark() {};
};