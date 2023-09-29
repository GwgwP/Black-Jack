#include "Event.h"
#include "sgg/graphics.h"
#include "Card.h"
#include "defines.h"
#include "Player.h"

void Event::update()
{
    if (!m_active)
    {
        return;
    }
    
    if (waiting()) 
    {
        m_elapsed_delay += graphics::getDeltaTime() / 1000.f; //convert to seconds
        return;
    }

    m_elapsed_time += graphics::getDeltaTime() / 1000.f;

    if (m_elapsed_time > m_duration) 
    {
        m_active = false;
    }
}

Event::Event(const float posx, const float posy, const float duration, const float delay)
    :m_pos_x(posx), m_pos_y(posy), m_duration(duration), m_delay(delay)
{}

const bool Event::active() const
{
    return m_active;
}

void Event::disable()
{
    m_active = false;
}

const bool Event::waiting() const
{
    return m_elapsed_delay < m_delay;
}


/****   1st SUBCLASS 
/************************************   Image Fade Out    ***********************************************************/

ImageFadeOut::ImageFadeOut(const float posx, const float posy, const std::string& path, const float size, const Scaling mode, const std::string& sound, float vol)
    :Event(posx, posy, 2.0f, 0.0f), m_path(path), m_size(size), m_mode(mode), m_scale(0.8f + rand0to1() * 0.4f), m_coeff(rand0to1())
{
    graphics::playSound("assets/sounds/"+sound+".mp3", vol);
}

void ImageFadeOut::draw() const
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    

    float s = m_elapsed_time / m_duration;

    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

    br.fill_opacity = 1 - s;
    br.texture = m_path;
    
    float scaling = 0.0f;
    if (m_mode != NONE) //if mode == NONE we don't need any scaling, so it will remain zero
    {
        scaling = powf(-1, m_mode)*s;
    }
    graphics::setScale(m_scale + scaling , m_scale + scaling); 
    
    graphics::drawRect(m_pos_x, m_pos_y, (1+m_coeff)*m_size, (1 + m_coeff) * m_size, br);
    graphics::resetPose();
}

/****   2nd SUBCLASS
/************************************   CARD MOTION    ***********************************************************/

CardMotionEvent::CardMotionEvent(const float start_x, const float start_y, const float stop_x, const float stop_y, Card* const card)
    :Event(0.0f, 0.0f, distance(start_x, start_y, stop_x, stop_y)/8.5f, 0.0f), m_start_x(start_x), m_start_y(start_y), m_stop_x(stop_x), m_stop_y(stop_y), m_card(card)
{
}
   /*       for duration : (v = velocity)
            v = Dx/Dt <=> Dt = Dx/v  ... Dx is the distance between y's and x's and v = 8.5        */

void CardMotionEvent::update()
{
    Event::update(); //update time metrics (inherited from base class 'Event')
 
    if (!m_card)
    {
        m_active = false;
        return;
    }

    if (waiting()) //redundant but for the sake of constistency
    {
        return;
    }
    
    //linear interpolation for smooth motion 
    float s = m_elapsed_time / m_duration;
    float x = m_start_x * (1.0f - s) + m_stop_x * s; 
    float y = m_start_y * (1.0f - s) + m_stop_y * s;

    m_card->setPosX(x);
    m_card->setPosY(y);
}

/****  3rd SUBCLASS
/************************************   Bird DRAW   ***********************************************************/

BirdDrawEvent::BirdDrawEvent()
    :Event((CANVAS_WIDTH - 4)* rand0to1() + 2, (CANVAS_HEIGHT - 4)* rand0to1() + 2, 4.0f, 0.0f), 
    m_stop_x (m_pos_x + rand0to1() * (CANVAS_WIDTH))
{
    m_orientation = 0.0f; 
    m_scale = 0.8f + rand0to1() * 0.4f;   
    m_size = rand0to1();
}

void BirdDrawEvent::draw() const
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    float curr_x;

    float s = m_elapsed_time / m_duration;

    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

    br.fill_opacity = 1 - s;
    br.texture = "assets/birds.png";

    graphics::setScale(m_scale - s, m_scale - s);
    graphics::setOrientation(m_orientation + s * 20);

    curr_x = m_pos_x * (1.0f - s) + m_stop_x * s;

    graphics::drawRect(curr_x, m_pos_y, (1 + m_size) * WIND_SIZE, (1 + m_size) * WIND_SIZE, br);
    graphics::resetPose();
}

/****   4th SUBCLASS
/************************************   Player's motion   ***********************************************************/

MotionAnimation::MotionAnimation(const float start_x, const float start_y, const float stop_x, const float stop_y, Player* const player)
    :Event(0.0f, 0.0f, 3.0f, 2.0f), m_start_x(start_x), m_start_y(start_y), m_stop_x(stop_x), m_stop_y(stop_y), m_player(player)
{
    x[0] = m_start_x;
    x[1] = (m_start_x + m_stop_x) / 2;
    x[2] = m_stop_x;

    y[0] = m_start_y;
    y[1] = (m_start_y + m_stop_y) / 2 - 3.2f; 
    y[2] = m_stop_y;
}

void MotionAnimation::update()
{

    Event::update(); //update time metrics (inherited from base class 'Event')

    if (!m_active)
    {
        return;
    }
    if (waiting())   //redundant but for the sake of constistency
    {
        return;
    }

    //checking with tolerance so that comparisons don't fail due to precision loss
    if (!m_player || (distance(m_start_x, m_start_y, m_stop_x, m_stop_y) < 0.5f))
    {
        m_active = false;
        return;
    }

    float s = m_elapsed_time / m_duration;
    float curr_x = m_start_x * (1.0f - s) + m_stop_x * s;

    float curr_y = 0.f;

    /************ Lagrange Interpolation ******************/
    for (int i = 0; i < 3; ++i)
    {
        float p = 1.0f;

        for (int j = 0; j < 3; ++j)
        {
            if (i != j)
            {
                p = p * (curr_x - x[j]) / (x[i] - x[j]); //SUM Li[x]*f[xi]
            }
        }
        curr_y += p * y[i];
    }
    m_player->setCurrX(curr_x);
    m_player->setCurrY(curr_y);
}


/****  5th SUBCLASS
/************************************   FADE FROM BLACK   ***********************************************************/

void FadeFromBlack::draw() const
{
    if (waiting())
    {
        return;
    }

    graphics::Brush br;
    SET_COLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
    br.outline_opacity = 0.0f;

    float s = m_elapsed_time / m_duration;
    br.fill_opacity = 1.0f - s;

    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

FadeFromBlack::FadeFromBlack()
    :Event(0.0f, 0.0f, 1.0f, 0.0f)
{}