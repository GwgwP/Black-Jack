#pragma once
#include <string>

class Event
{
protected:
	const float m_pos_x; 
	const float m_pos_y;				

	const float m_duration;					
	float m_elapsed_time = 0.0f;

	const float m_delay;						
	float m_elapsed_delay = 0.0f;
	
	bool m_active = true; 

public:
	Event(const float posx, const float posy, const float duration, const float delay);
	virtual void draw() const {} ;
	virtual void update();
	const bool active() const;
	void disable();
	const bool waiting() const;
	virtual ~Event() { };
};

/*********************************    IMAGE FADE OUT     ****************************************************************/

class ImageFadeOut
	:public Event
{
public:
	enum Scaling{INCREASE, DECREASE, NONE};
protected:

	const Scaling m_mode;
	const float m_scale;
	const float m_coeff;
	const std::string m_path;
	float m_size;

public:						
	ImageFadeOut(const float posx, const float posy, const std::string& path, const float size, const Scaling mode, const std::string& sound, const float vol);
	void draw() const override;
	~ImageFadeOut() {};
};

/*********************************    CARD MOTION     ****************************************************************/

class CardMotionEvent
	:public Event
{
	class Card* const m_card;

	const float m_start_x;
	const float m_start_y;

	const float m_stop_x; 
	const float m_stop_y;

public:
	CardMotionEvent(const float start_x, const float start_y, const float stop_x, const float stop_y, class Card* const card);
	void update();
	~CardMotionEvent() {};
};

/*********************************    Bird Draw     ****************************************************************/
class BirdDrawEvent
	:public Event
{
	float m_orientation;
	float m_scale;

	const float m_stop_x; 

	float m_size;

public:
	BirdDrawEvent();
	void draw() const override;	 
	~BirdDrawEvent(){}
};

/**********************************		Player's Motion   ***********************************************************/
class MotionAnimation
	:public Event
{
	class Player* const m_player;

	const float m_start_x;
	const float m_start_y;
	
	const float m_stop_x;
	const float m_stop_y;

	float x[3];		//for interpolation
	float y[3];

public:
	MotionAnimation (const float start_x, const float start_y, const float stop_x, const float stop_y, class Player* const player);
	void update();
	~MotionAnimation() {};
};

/**********************************		Black Fade    ***********************************************************/
class FadeFromBlack
	:public Event
{
public:
	FadeFromBlack();
	void draw() const override;	
	~FadeFromBlack(){}
};