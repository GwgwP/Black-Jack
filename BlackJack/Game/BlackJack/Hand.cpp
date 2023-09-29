#include "Hand.h"
#include "sgg/graphics.h"
#include "PlainCard.h"
#include "AceCard.h"

#define initial_center m_posX-m_width/2 + CARD_WIDTH/2+0.3f


Hand::Hand(const float posX, const float posY)
	:Scopable(posX, posY, HAND_WIDTH, HAND_HEIGHT), m_curr_cards_center(initial_center), m_active(false), m_hands_value(0)
{
	cards.reserve(10); 
}

const bool Hand::addCard(Card* c)
{
	
	graphics::playSound("assets/sounds/PlayingCard.mp3", 0.8f);

	//Placing cards in the right position of player's hand. 
	if (cards.size() > 4)
	{
		if (cards.size() == 5)
		{
			m_curr_cards_center = initial_center;
		}
		c->setPosX(m_curr_cards_center);
		c->setPosY(HANDS_Y + 1.5f);
	}
	else
	{
		c->setPosX(m_curr_cards_center);
		c->setPosY(HANDS_Y);
	}

	m_curr_cards_center += CARD_WIDTH / 2;
	cards.push_back(c);
	

	if (cards.size() == 2 && m_hands_value + c->getValueOfCard() == 21)
	{
		m_BlackJack = true;
		m_hands_value = 21;
		return true;
	}
	int temp = m_hands_value;
	temp += c->getValueOfCard();	
	bool noMoreAces = false;

	while (temp > 21 && !noMoreAces)	
	{	
		for (auto card : cards)
		{
			if (card->getValueOfCard() == 11) //Fixing value of AceCards according to player's needs
			{
				noMoreAces = false;	//Found an AceCard
				static_cast<AceCard*> (card)->setAsOne(true);
				temp -= 11;
				temp += 1;
							//jump back to while loop to check if temp is still > 21. 
				break;		//If not, no other AceCard should be modified.			
			}
			noMoreAces = true;	
			/* if an AceCard had been found then 'noMoreAces' would have remained false
			*  and program wouldn't have reached this line of code
			*  because of break statement.
			*/
		}
	}
	m_hands_value = temp;

	return (m_hands_value >= 21);
}

void Hand::draw() const
{	
	graphics::Brush br;
	
	br.outline_opacity = m_active;
	SET_COLOR(br.outline_color, 0.1f, 0.0f, 0.0f);
	br.outline_width = 1.35f;

	SET_COLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	br.fill_opacity=0.3f;
	graphics::drawRect(m_posX, m_posY, m_width, m_height, br);
	
	for (auto c : cards)
	{			
		c->setFront(m_active);	
		c->draw();
	}

	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 0.8f*m_active;

	graphics::setFont("assets/Bleeding_Cowboys.ttf");
	graphics::drawText(m_posX - 1.0f, m_posY - m_height/2 - 0.7f, 0.7f, "Score:   " + std::to_string(m_hands_value), br);
}

const bool Hand::hasBlackJack() const
{
	return m_BlackJack;
}

const uint Hand::getValueofHand() const
{
	return m_hands_value;
}

const size_t Hand::getSize() const
{
	return cards.size();
}

void Hand::setActive(const bool active)
{
	m_active = active;
}

const bool Hand::isActive() const
{
	return m_active;
}

Hand::~Hand()
{
	for (auto card : cards)
	{
		delete card;
	}
	cards.clear();
}