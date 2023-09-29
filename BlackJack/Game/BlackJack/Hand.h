#pragma once
#include "Card.h"
#include <vector>
#include "defines.h"
#include "Scopable.h"

class Hand final
	: public Scopable
{
private:
	std::vector <Card*> cards;
	float m_curr_cards_center;
	uint m_hands_value;
	bool m_BlackJack = false;

	bool m_active;
	
public:
	Hand(const float posX, const float PosY);
	const bool addCard(Card* c); 
	void draw() const override;
	
	const bool hasBlackJack() const;
	const uint getValueofHand() const;
	const size_t getSize() const;
	
	void setActive(const bool active);
	const bool isActive() const;

	~Hand();
};