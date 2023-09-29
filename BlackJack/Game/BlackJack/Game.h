#pragma once
#include <sgg/graphics.h>
#include "GameButton.h"
#include "Player.h"
#include "Button.h"
#include "Deck.h"
#include "Card.h"
#include <vector>
#include <list> 
#include "Mark.h"
#include "Level.h"
#include <string>
#include "Event.h" 
#include "defines.h"
#include "HelpButton.h"
#include "Selectable.h"
#include "MusicButton.h"
#include "WindowButton.h"
#include <string>
#include <map>


class Game final
{
public:
	enum gameStates { INIT, LOADING, IDLE_DASH, DASHBOARD, INIT_ROUND, IDLE_BJ, MOVING_CARD, STANDPHASE, TOGGLE, MARK_SELECT, ROUND_OVER, ROUND_WINNER, CLEAR_ROUND, GAME_OVER, _size };
	

private:
	static Game* m_instance;

	std::map<Game::gameStates, std::pair<std::string, float>> state_n_music;

	Game() //singleton class
	{
		for (gameStates state = gameStates::INIT; state < gameStates::_size; state = static_cast<gameStates>(static_cast<int>(state) + 1))
			if (state <= LOADING)
				state_n_music.insert({ state, std::pair<std::string, float>("loading", 0.45f) });
			else if (state <= INIT_ROUND || state==GAME_OVER)
				state_n_music.insert({ state, std::pair<std::string, float>("trivia", 0.45f) });
			else if (state <= CLEAR_ROUND)
				state_n_music.insert({ state, std::pair<std::string, float>("dramatic", 0.15f) });
	};		

	gameStates m_state = INIT;
	

	Mark* m_active_Mark = nullptr;
	Player* m_winner = nullptr; 
	Player* m_player_Jack = nullptr; 
	Player* m_player_Jill = nullptr;	
	Player* m_active_Player = nullptr;
    Card* m_active_Card = nullptr;
	Deck* m_deck = nullptr;
	

	bool m_volume = true;
	bool m_valid_Action = false;
	bool m_over = false;	//if the player exceeds the limit of 21 => immediate over of round.
	

	uint m_rounds = 0;
	uint m_marks_selected = 0;
	uint m_player_Standed = 0;

	std::deque<Selectable*> DashSelectables;	//Dashboard Selectables
	std::deque<Selectable*> BJSelectables;		//Black Jack Selectables
	std::deque<Selectable*> MarkCollection;
	std::deque<Selectable*> GOSelectables;		//Game Over Selectables

	std::list<Event*> m_events;

	std::vector<Level*> m_levels;

	bool false_stand = false; 

	void togglePlayer(); 
	const Player* player_toStand() const;
	void pressEnterMessg(graphics::Brush& br, const bool red = false) const ;

	void drawBackground(graphics::Brush& br, const std::string& bitmap) const;

	void roundInit();
	void clearRound();

	void processEvents();
	void addEvent(Event* event);

	Selectable* const handleSelectables(std::deque<Selectable*>& selectables, const graphics::MouseState ms, const float mx, const float my) const ;
	
	void destroy();

public:		
	void draw();
	static Game* const getInstance();
	void update();
	
	void init();
	
	const Level* const getLevel(const Level* currLevel, const uint steps) const ;
	const Level* peekLastLevel();
	const gameStates getState() const;

	void setVolume(const bool vol);

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	void setState(const Game::gameStates state) { m_state = state; };
	~Game(); //must delete every instance of dynamically allocated memory
};