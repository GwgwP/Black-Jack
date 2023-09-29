#pragma once
#include "Scopable.h"
#include "defines.h"

class Level final
	:public Scopable
{
protected:
	static uint numOfLevels;
	const uint m_id;
	const uint m_cordX, m_cordY;

	bool m_hover = false;

public:
	Level(const uint cordX, const uint cordY);
	const uint getId() const;
	const uint getCordX() const;
	const uint getCordY() const;
	void draw() const override;

	void setHover(const bool hover);

	static void reset();
	~Level() {};
};