#pragma once
#include "sgg/graphics.h"
#include "Scopable.h"
#include "defines.h"

class Card
	: public Scopable
{

public:
	enum Suits { HEARTS, CLUBS, SPADES, DIAMONDS };

protected:
	Suits m_suit;
	bool m_front = false; //face (m_front = true) or back side (m_front = false) of card

private:		
	void drawBackSide(graphics::Brush& br) const; //every type of card uses the same drawBackSide() function
	
public:
	Card(const Suits& s);
	virtual void draw() const;
	virtual const uint getValueOfCard() const = 0;
	void setFront(const bool front);
	void setPosX(const float posX);
	void setPosY(const float posY);
	const float getPosX() const;
	const float getPosY() const;
	virtual ~Card() {  };
};