#pragma once
#include "defines.h"
#include "sgg/graphics.h"
#include "Hand.h"
#include "Mark.h"
#include "Level.h"

class Player final
{
public:
	enum playerName { JACK, JILL };

protected:
	const playerName m_name;

	bool m_active; 

	Hand* m_hand;		
	Mark* m_mark;
	
	const Level* m_level;		

	float m_curr_posx; 
	float m_curr_posy;	 

	float m_next_posx; 
	float m_next_posy;	 

public: 
	Player(const playerName& name, Level* level); 
	void draw() const;
	void update(const bool wonRound);
	Hand* const getHand() const;
	void setMark(Mark* mark);
	bool hasBlackJack();
	const std::string getName() const;		
	void clearHand() ;
	const bool wonGame() const ;

	const float getCurrX() const;
	const float getCurrY() const;

	const float getNextX() const;
	const float getNextY() const ;

	void setCurrX(const float x);
	void setCurrY(const float y);

	void setActive(const bool active);
	const bool isActive() const ;

	~Player();
};