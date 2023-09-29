#pragma once

#include "Selectable.h"
#include "AceCard.h"
#include "PlainCard.h"
#include "FigureCard.h"
#include "defines.h"
#include <deque>

class Deck final
	:public Selectable
{

private:
	std::deque<Card*> deck;
	Card* topCard;

	bool m_popped;

	void shuffleCards();

	float m_orientation;

public:
	Deck();
	void draw() const override;
	void onClick() override;
	void setPopped();
	Card* const getTopCard() const;
	void removeCard();

	~Deck();
};