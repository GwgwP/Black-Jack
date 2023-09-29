#include "Player.h"
#include "Game.h"


Player::Player(const playerName& name,  Level* level)
	: m_name(name), m_level(level), m_active(false)  //m_level = initial level
{
	int pos_x = m_level->getCordX();
	int pos_y = m_level->getCordY();

	if (m_name == JACK)
	{
		m_hand = new Hand(JACKS_HAND_X, HANDS_Y);
		m_curr_posx = pos_x * SQUARE_SIZE + 1.0f;
		m_curr_posy = pos_y * SQUARE_SIZE + 1.5f;
	}
	else
	{
		m_hand = new Hand(JILLS_HAND_X, HANDS_Y);
		m_curr_posx = pos_x * SQUARE_SIZE + 2.5f;
		m_curr_posy = pos_y * SQUARE_SIZE + 1.5f;
	}
	
	m_next_posx = m_curr_posx;
	m_next_posy = m_curr_posy;
	
	m_mark = nullptr;	//setMark assigns a mark object to m_mark
	
}



void Player::draw() const
{
	Game::gameStates state = Game::getInstance()->getState();

	graphics::Brush pl;
	pl.fill_opacity = 1.0f;
	SET_COLOR(pl.fill_color, 1.0f, 1.0f, 1.0f);
	pl.outline_opacity = 0.0f;

	if (state == Game::gameStates::DASHBOARD || state == Game::gameStates::IDLE_DASH)
	{
		int pos_x = m_level->getCordX();
		int pos_y = m_level->getCordY();


		if (m_name == JACK)
		{
			pl.texture = "assets/jack2.png";
			graphics::drawRect(m_curr_posx, m_curr_posy, 3.5f, 3.5f, pl);
		}
		else
		{
			pl.texture = "assets/jill.png";
			if (pos_x != 0)
			{
				graphics::drawRect(m_curr_posx, m_curr_posy, 3.066f, 3.136f, pl);
			}
			else
			{
				graphics::drawRect(m_curr_posx, m_curr_posy, 2.912f, 2.847f, pl);
			}
		}
		return;
	}
	if (state == Game::gameStates::IDLE_BJ || state == Game::gameStates::MOVING_CARD || state == Game::gameStates::TOGGLE || state == Game::gameStates::STANDPHASE)
	{
		m_hand->draw();
		return;
	}
	if (state == Game::gameStates::ROUND_WINNER)
	{
		std::string path = "assets/Winner" + getName();
        pl.texture = path + ".png";
        graphics::drawRect(CANVAS_WIDTH * 3 / 4, CANVAS_HEIGHT * 3 / 4, CANVAS_WIDTH / 2, CANVAS_WIDTH / 2, pl);
	
		return;
	}
	if (state == Game::gameStates::GAME_OVER)
	{
		pl.texture = "assets/" + getName() + "wins.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, pl);
		
		return;
	}
}

void Player::update(const bool wonRound)
{

	int steps = pow((-1), (wonRound + 1) ) * m_mark->getValue();

	const Level* prevLevel = m_level;
	m_level = Game::getInstance()->getLevel(m_level, steps); //m_level = next level 

	if (prevLevel == m_level)
	{
		m_next_posx = m_curr_posx;
		m_next_posy = m_curr_posy;
		return;
	}

	int pos_x = m_level->getCordX();
	int pos_y = m_level->getCordY();

	if (m_name == JACK)
	{
		m_next_posx = pos_x * SQUARE_SIZE + 1.0f;
		m_next_posy = pos_y * SQUARE_SIZE + 1.5f; 
	}
	else
	{
		m_next_posx = pos_x * SQUARE_SIZE + 2.5f;
		m_next_posy = pos_y * SQUARE_SIZE + 1.5f;
	}	
}

Hand* const Player::getHand() const
{
	return m_hand;
}

void Player::setMark( Mark* mark)
{
	m_mark = mark;
}

bool Player::hasBlackJack()
{
	return m_hand->hasBlackJack();
}

const std::string Player::getName() const
{
	return m_name == JACK ? "Jack" : "Jill";
}

void Player::clearHand()
{
	delete m_hand;
	if (m_name == JACK)
	{
		m_hand = new Hand(JACKS_HAND_X, HANDS_Y);
	}
	else
	{
		m_hand = new Hand(JILLS_HAND_X, HANDS_Y);
	}	
}

const bool Player::wonGame() const
{
	return (m_level == Game::getInstance()->peekLastLevel());
}

const float Player::getCurrX() const 
{
	return m_curr_posx;
}

const float Player::getCurrY() const
{
	return m_curr_posy;
}

const float Player::getNextX() const
{
	return m_next_posx;
}

const float Player::getNextY() const
{
	return m_next_posy;
}

void Player::setCurrX(const float x)
{
	m_curr_posx = x;
}

void Player::setCurrY(const float y)
{
	m_curr_posy = y;
}

void Player::setActive(const bool active)
{
	m_active = active;
	m_hand->setActive(active);
}

const bool Player::isActive() const
{
	return m_active;
}

Player::~Player()
{
	if (m_hand)
	{
		delete m_hand;
		m_hand = nullptr;
	}
}