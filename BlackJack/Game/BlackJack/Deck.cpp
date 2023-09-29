#include "Deck.h"

#include <algorithm> 


void Deck::shuffleCards()
{
	std::random_shuffle(deck.begin(), deck.end()); 
}

Deck::Deck() 
	:Selectable(CANVAS_WIDTH/2, CANVAS_HEIGHT/4, DECK_WIDTH, DECK_HEIGHT), m_popped(false), topCard(nullptr)
{
	//initialize deck with:

	//36 plain cards
	for (PlainCard::Suits s = PlainCard::Suits::HEARTS; s <= PlainCard::Suits::DIAMONDS; s = static_cast<PlainCard::Suits>(static_cast<int>(s) + 1))
		for (PlainCard::Ranks r = PlainCard::Ranks::TWO; r <= PlainCard::Ranks::TEN; r = static_cast<PlainCard::Ranks>(static_cast<int>(r) + 1))
			deck.push_back(new PlainCard(s, r));

	//12 figure cards
	for(FigureCard::Suits s = FigureCard::Suits::HEARTS; s <= FigureCard::Suits::DIAMONDS; s = static_cast<FigureCard::Suits>(static_cast<int>(s) + 1))
		for (FigureCard::Ranks r = FigureCard::Ranks::JACK; r <= FigureCard::Ranks::KING; r = static_cast<FigureCard::Ranks>(static_cast<int>(r) + 1))
			deck.push_back(new FigureCard(s, r));
	

	//and 4 aces
	for (AceCard::Suits s = AceCard::Suits::HEARTS; s <= AceCard::Suits::DIAMONDS; s = static_cast<AceCard::Suits>(static_cast<int>(s) + 1))
		deck.push_back(new AceCard(s));

	
	//then shuffle all cards
	shuffleCards();
}

void Deck::draw() const
{
	//highlighting
	Selectable::draw();

	//deck
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	br.fill_opacity = 1.0f;

	br.texture = "assets/deck.png";
	graphics::setOrientation(m_orientation);
	graphics::drawRect(m_posX, m_posY, DECK_WIDTH, DECK_HEIGHT, br);
	graphics::resetPose();
}

void Deck::onClick()
{
	m_orientation += pow((-1), m_orientation > 0) * (rand0to1() * 10.0f);
	
	if (!m_enable)
	{
		graphics::playSound("assets/sounds/error.mp3", 0.3f);
		return;
	}
	
	if (!m_popped) 
	{
		graphics::playSound("assets/sounds/deck.mp3", 0.8f);
		topCard = deck.front();
		m_popped = true;
	}
	else
	{
		graphics::playSound("assets/sounds/blip.mp3", 0.3f);
	}
}

Card* const Deck::getTopCard() const 
{
	if (!m_popped)
	{
		return nullptr;
	}
	return topCard;
}

void Deck::removeCard()
{
	deck.pop_front();
}

void Deck::setPopped() //when active card enters player's hand
{
	m_popped = false;
}

Deck::~Deck()
{
	for (auto c : deck)
		delete c;
	deck.clear();
}
