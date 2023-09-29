#pragma once
#include <random>
#include <stdlib.h>

typedef unsigned int uint

#define CANVAS_HEIGHT 15.0f
#define CANVAS_WIDTH 24.0f

#define SQUARE_SIZE 3.0f

#define ROCK_HEIGHT 1.648f
#define ROCK_WIDTH 2.536f

#define CARD_WIDTH 3.033f
#define CARD_HEIGHT 4.5306f

#define CENTER_SUIT_WIDTH 1.5f
#define CENTER_SUIT_HEIGHT 1.5f
#define CORNER_SUIT_WIDTH 0.5f
#define CORNER_SUIT_HEIGHT 0.5f
#define CORNER_RANK_WIDTH 0.4f
#define CORNER_RANK_HEIGHT 0.5f

#define CENTER_FIGURE_WIDTH 2.25f
#define CENTER_FIGURE_HEIGHT 4.0f
#define CENTER_ACE_WIDTH 2.25f
#define CENTER_ACE_HEIGHT 2.25f

#define POP_POSITION_X CANVAS_WIDTH/4
#define POP_POSITION_Y CANVAS_HEIGHT/4


#define DECK_WIDTH 3.033f + 0.5f
#define DECK_HEIGHT 4.5306f +0.5f

#define HAND_WIDTH 10.f
#define HAND_HEIGHT 5.f

#define BUTTON_WIDTH 2.25f
#define BUTTON_HEIGHT 1.5f
#define MUSIC_BUTTON 0.95f

#define EXPLOSION_SIZE 4.0f
#define DUST_SIZE 2.0f
#define BADGE_SIZE 2.0f
#define WIND_SIZE 5.0f 
#define CLOCK_SIZE 2.5f
#define BLACKJACK_SIZE 8.0f


#define PAPYRUS_WIDTH 20.0f
#define PAPYRUS_HEIGHT 14.0f

#define RULES_WIDTH	17.36f
#define RULES_HEIGHT 8.0f

#define JACKS_HAND_X CANVAS_WIDTH / 4
#define HANDS_Y CANVAS_HEIGHT * 3 / 4
#define JILLS_HAND_X CANVAS_WIDTH *3/4


#define MARK_RADIUS 4.0f

#define SET_COLOR(c ,r ,g ,b) {c[0] = r; c[1]=g; c[2]=b;}

;
inline float rand0to1()
{
	return rand() / (float)RAND_MAX;	
};

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
};