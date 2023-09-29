#include "Game.h"

void Game::draw()
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    SET_COLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

    if (m_state == INIT)
    {
        drawBackground(br, "loading");

        graphics::setFont("assets/docktrin.ttf"); 
        br.fill_opacity = 0.8f;
        graphics::drawText(CANVAS_WIDTH * 3 / 4, CANVAS_HEIGHT / 2, 0.7f, "Loading...", br);

        m_state = LOADING;
    }
    else if(m_state == LOADING)
    {
        return;
    }
    else if (m_state == DASHBOARD || m_state == IDLE_DASH)
    {
        drawBackground(br, "dash");

        for (auto lvl : m_levels)
        {
            lvl->draw();
        }
        
        m_player_Jack->draw();
        m_player_Jill->draw();

        for (auto sel : DashSelectables) {
            sel->draw();
        }
    }
    else if (m_state == IDLE_BJ || m_state == MOVING_CARD || m_state == TOGGLE || m_state == STANDPHASE )
    {
        if (false_stand)
        {
            graphics::setFont("assets/CATChilds.ttf");
            float r = 0.8f;
            SET_COLOR(br.fill_color, r, 0.0f, 0.0f);
            graphics::drawText(CANVAS_WIDTH / 8, CANVAS_HEIGHT * 7 / 9, 0.6f, "You have to drag a/the card to your hand first.", br);
            graphics::drawText(CANVAS_WIDTH / 8, CANVAS_HEIGHT*7.5/9, 0.6f, "Then if you wish to stand, press the STAND button again.", br);
        }
        //background Black Jack
        drawBackground(br, "felt");

        m_player_Jack->draw();
        m_player_Jill->draw();

        if (m_active_Card)
        {
            m_active_Card->draw(); //m_front = false by default
        }

        for (auto sel : BJSelectables)
        {
            sel->draw();
        }
    }
    else if (m_state == MARK_SELECT)
    {
        drawBackground(br, "markbg");

        graphics::setFont("assets/docktrin.ttf");
        graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 4, 1.0f, m_active_Player->getName() + " Make your Deal ", br);

        for (auto mark : MarkCollection)
        {
            mark->draw();
        }

        //Press enter to continue msg
        if (m_active_Mark)
        {
            pressEnterMessg(br, true);
        }
    }
    
    else if (m_state == ROUND_OVER)
    {
        return;
    }
  
    else if (m_state == ROUND_WINNER)
    {
        if (m_winner)
        {
            drawBackground(br, "felt");

            m_winner -> draw();

            graphics::setFont("assets/docktrin.ttf");
            graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 4, 1.0f, "Winner Of Round", br);
            graphics::drawText(CANVAS_WIDTH / 2 + 0.5, CANVAS_HEIGHT / 4 - 0.8f, 2.5f, std::to_string(m_rounds), br); 

            //for badge
            graphics::MouseState ms;
            graphics::getMouseState(ms);
            float mx = graphics::windowToCanvasX(ms.cur_pos_x);
            float my = graphics::windowToCanvasY(ms.cur_pos_y);

            br.texture = "assets/badge.png";
            graphics::drawRect(mx, my, BADGE_SIZE, BADGE_SIZE, br);

            //press enter to continue msg
            pressEnterMessg(br);
        }
        else
        {
            drawBackground(br, "drawJack_Jill");
           
            graphics::setFont("assets/docktrin.ttf");
            graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 4, 1.0f, "Round", br);
            graphics::drawText(CANVAS_WIDTH / 4 + 1.5f, CANVAS_HEIGHT / 4 - 0.8f, 2.5f, std::to_string(m_rounds), br);
            graphics::drawText(CANVAS_WIDTH / 4 + 0.6f, CANVAS_HEIGHT / 3, 0.8f, "it's a draw!", br);

            //press enter to continue msg
            pressEnterMessg(br);
        }
    }
    else if (m_state == GAME_OVER)
    { 
        m_winner->draw();
       
        br.texture = "assets/GOmess.png";
        graphics::drawRect(CANVAS_WIDTH / 8, CANVAS_HEIGHT/8, 5.71f, 4.37f, br); 
       
        for (auto sel : GOSelectables)
        {
            sel->draw();
        }
    }

    //draw every active event 
    for (auto ev : m_events)
    {
        ev->draw();
    }
    return;
}

void Game::update()
{
    if (m_state == INIT)
    {
        return;
    }

    if (m_state == LOADING)
    {
        //initialize Game
        init();

        graphics::playMusic("assets/music/trivia.mp3", 0.45f * m_volume, true, 3000);
        m_state = DASHBOARD;   
        return;
    }

    //update list of events (remove and delete any inactive events)
    processEvents();
  
    m_player_Jack->setActive(m_active_Player == m_player_Jack);
    m_player_Jill->setActive(m_active_Player == m_player_Jill);

    if (m_state == DASHBOARD)
    {
        if (m_events.empty()) //w8 until the animation is over
        {
            if (m_winner && m_winner->wonGame())
            {
                //"when you reach the top, keep climbing mp3"
                std::string path = m_winner->getName();
                graphics::playSound("assets/sounds/" + path + "_end.mp3", 0.8f);

                m_state = GAME_OVER;
            }
            else
            {
                m_state = IDLE_DASH;
            }
        }
    }

    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    if (m_state == IDLE_DASH)
    {
        handleSelectables(DashSelectables, ms, mx, my);

        for (auto lvl : m_levels)
        {
            bool hover = lvl->inScope(mx, my) && lvl->enableSignal();
            lvl->setHover(hover);
        }

        //When Play Button is pressed --> m_state = INIT_ROUND;
        return;
    }

    if (m_state == INIT_ROUND)
    {
        //initialize every round
        roundInit();
        addEvent(new FadeFromBlack()); 
        m_state = MARK_SELECT;
        graphics::playMusic("assets/music/dramatic.mp3", 0.15f * m_volume, true, 3000);
        return;
    }

    if (m_state == MARK_SELECT)
    {
        Selectable* temp = handleSelectables(MarkCollection, ms, mx, my);
        if (temp)
        {
            m_active_Mark = static_cast<Mark*>(temp);
            m_active_Mark->setActive(true);
        }

        for (auto mark : MarkCollection)
        {
            if (mark != m_active_Mark)
            {
                static_cast<Mark*>(mark)->setActive(false);
            }
        }
        if (m_active_Mark && graphics::getKeyState(graphics::SCANCODE_RETURN))
        {
            graphics::playSound("assets/sounds/mark.mp3", 0.7f);
            m_marks_selected++;

            m_active_Player->setMark(m_active_Mark);

            m_active_Mark = nullptr;
            togglePlayer();

            if (m_marks_selected == 2) //if both players have selected their mark move on to next state
            {
                m_state = IDLE_BJ;
                return;
            }
        }
        return;
    }
    if (m_state == IDLE_BJ || m_state == MOVING_CARD ) 
    {
        handleSelectables(BJSelectables, ms, mx, my);
        
        m_active_Card = m_deck->getTopCard();

        if (m_active_Card && m_active_Card->enableSignal() && m_active_Card->inScope(mx, my) && ms.dragging)
        {
            m_state = MOVING_CARD;

            //moving card...
            m_active_Card->setPosX(mx);
            m_active_Card->setPosY(my);

            //if the mouse is in scope of active player's hand in the last update cycle
            if (m_active_Player->getHand()->inScope(mx, my))
            {
                m_valid_Action = true;
                false_stand = false;
            }
            else
            {
                m_valid_Action = false;
            }
        }

        //if the card was moving and then was released
        if (m_active_Card && m_state == MOVING_CARD && ms.button_left_released)
        {
            if (!m_valid_Action)
            {
                float x_init = m_active_Card->getPosX();
                float y_init = m_active_Card->getPosY();

                //move card back to initial (pop) position
                addEvent(new CardMotionEvent(x_init, y_init, POP_POSITION_X, POP_POSITION_Y, m_active_Card));
            }
            else
            {
                //add Card to active player's hand and check if there is an immediate win/loss
                m_over = m_active_Player->getHand()->addCard(m_active_Card);
               

                m_deck->removeCard();

                m_deck->setPopped();  //enable next card to be popped...

                addEvent(new ImageFadeOut(CANVAS_WIDTH * 3 / 4, CANVAS_HEIGHT / 4, "assets/clock.png", CLOCK_SIZE, ImageFadeOut::Scaling::NONE, "clock", 0.4f));
                m_state = TOGGLE;
                return;
            }
        }
        return;
    }

    if (m_state == TOGGLE)
    {       
        if (m_over && m_events.empty()) //w8 until the animation is over and then move on to next state
        {
            m_state = ROUND_OVER;
            return;
        }

        if (m_events.empty())
        {
            m_state = IDLE_BJ;
            if (m_player_Standed == 0)
            {  
                togglePlayer();
            }
        }
    }
    if (m_state == STANDPHASE)
    {

        //invalid stand action

        //if active player drew a card from the deck, and then pressed STAND button
        //without putting the active card to his hand, it is considered as
        //invalid action and in order to continue the round they must put
        //the active card to their hand. Same if the player has less than 2 cards in their hand.

        if ((m_active_Card || player_toStand()->getHand()->getSize() < 2))
        {
            m_state = IDLE_BJ;
            false_stand = true;
            return;
        }

        //valid stand action

        std::string path = player_toStand()->getName();
        graphics::playSound("assets/sounds/" + path + "_stand.mp3", 0.8f);
        
        m_player_Standed++;
        
        m_state = IDLE_BJ;

        if (m_player_Standed == 2)
        {
            m_state = ROUND_OVER;
        }
        return;
    }

    if (m_state == ROUND_OVER)
    {
        //Determining winner...

        if (m_player_Jack->hasBlackJack())
        {
            m_winner = m_player_Jack;
            addEvent(new ImageFadeOut(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, "assets/blackJack.png", BLACKJACK_SIZE, ImageFadeOut::Scaling::NONE, "blackJack", 0.6f)); //new
        }
        else if (m_player_Jill->hasBlackJack())
        {
            m_winner = m_player_Jill;
            addEvent(new ImageFadeOut(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, "assets/blackJack.png", BLACKJACK_SIZE, ImageFadeOut::Scaling::NONE, "blackJack", 0.6f));
        }
        else
        {
            if (m_player_Jack->getHand()->getValueofHand() == m_player_Jill->getHand()->getValueofHand())
            {
                m_winner = nullptr;
            }
            else if (m_player_Jack->getHand()->getValueofHand() > 21)
            {
                m_winner = m_player_Jill;
            }
            else if (m_player_Jill->getHand()->getValueofHand() > 21)
            {
                m_winner = m_player_Jack;
            }
            else if (m_player_Jack->getHand()->getValueofHand() > m_player_Jill->getHand()->getValueofHand())
            {
                m_winner = m_player_Jack;
            }
            else if (m_player_Jill->getHand()->getValueofHand() > m_player_Jack->getHand()->getValueofHand())
            {
                m_winner = m_player_Jill;
            }
        }

        //update players' levels according to winner (if there is a winner)
        if (m_winner)
        {
            m_player_Jack->update(m_winner == m_player_Jack);
            m_player_Jill->update(m_winner == m_player_Jill);
        }
        addEvent(new FadeFromBlack()); 
        m_state = ROUND_WINNER;
        return;
    }
    if (m_state == ROUND_WINNER)
    {
        if (!m_winner)
        {
            if (rand0to1() < 0.6)    //probability 60%
            {                    
                addEvent(new ImageFadeOut(mx, my, "assets/dust.png", DUST_SIZE, ImageFadeOut::Scaling::INCREASE, "", 0.0f));
            }
            if (rand0to1() < 0.01)   //probability 1% 
            {          
                addEvent(new BirdDrawEvent());  
                graphics::playSound("assets/sounds/wind.mp3", 0.8f);
            }
        }
        else if (m_winner && rand0to1() < 0.01) //probability 1% 
        {
            addEvent(new ImageFadeOut((CANVAS_WIDTH - 4) * rand0to1() + 2, (CANVAS_HEIGHT - 4) * rand0to1() + 2, "assets/Explosion1.png", EXPLOSION_SIZE, ImageFadeOut::Scaling::INCREASE, "explosion", 0.65f));
        }

        if (graphics::getKeyState(graphics::SCANCODE_RETURN))
        {
            m_state = CLEAR_ROUND;
        }
        return;
    }
    
    

    if (m_state == CLEAR_ROUND)
    {
        clearRound();   //the dynamically allocated memory has to be released

        addEvent(new MotionAnimation(m_player_Jill->getCurrX(), m_player_Jill->getCurrY(), m_player_Jill->getNextX(), m_player_Jill->getNextY(), m_player_Jill));
        addEvent(new MotionAnimation(m_player_Jack->getCurrX(), m_player_Jack->getCurrY(), m_player_Jack->getNextX(), m_player_Jack->getNextY(), m_player_Jack));

        m_state = DASHBOARD;
        graphics::playMusic("assets/music/trivia.mp3", 0.45f * m_volume, true, 3000);
        return;
    }

    if (m_state == GAME_OVER)
    {
        handleSelectables(GOSelectables, ms, mx, my);
        
        if (m_state == LOADING)
        {
            destroy();
        }
        return;
    }
}

void Game::roundInit()
{
    
    m_deck = new Deck();
    BJSelectables.push_front(m_deck);

    m_over = false;
    m_marks_selected = 0;
    m_player_Standed = 0;


    m_active_Player = (m_winner ? m_winner : m_player_Jack);
    m_winner = nullptr; //for checking game Over

    m_rounds++;
}

void Game::clearRound()
{

    BJSelectables.pop_front();
    
    delete m_deck;
    m_deck = nullptr;

    m_player_Jack->clearHand();
    m_player_Jill->clearHand();

    m_active_Card = nullptr;
}

const Level* const Game::getLevel(const Level* currLevel, const uint steps) const //returns next level 
{
    int newId = currLevel->getId() + steps;
    if (newId < 0)
    {
        newId = 0;
    }
    else if (newId > m_levels.size() - 1)
    {
        newId = m_levels.size() - 1;
    }

    return m_levels.at(newId);
}

void Game::processEvents()
{
    for (auto evn : m_events)
    {
        evn->update();

    }

    //remove inactive events
    m_events.remove_if([](Event* evn) {bool temp = !evn->active(); if(temp) delete evn; return temp; });
}

void Game::addEvent(Event* event)
{
    m_events.push_front(event);
}

const Level* Game::peekLastLevel()
{
    return m_levels.at(m_levels.size() - 1);
}

const Game::gameStates Game::getState() const
{
    return m_state;
}

void Game::setVolume(const bool vol)
{
    m_volume = vol;
    if (m_volume) 
    {
        std::pair<std::string, float> music = state_n_music[m_state];
        graphics::playMusic("assets/music/" + music.first +".mp3", music.second, true, 3000);
    }
    else
    {
        graphics::stopMusic();
    }
}

void Game::init()
{
    graphics::playMusic("assets/music/loading.mp3", 0.45f);

    m_levels.reserve(10);
    
    //create levels
    m_levels.push_back(new Level(0, 4));
    m_levels.push_back(new Level(3, 4));
    m_levels.push_back(new Level(6, 3));
    m_levels.push_back(new Level(1, 3));
    m_levels.push_back(new Level(4, 2));
    m_levels.push_back(new Level(7, 1));
    m_levels.push_back(new Level(2, 1));
    m_levels.push_back(new Level(0, 0));
    m_levels.push_back(new Level(5, 0));
    m_levels.push_back(new Level(7, 0));


    //create players
    m_player_Jack = new Player(Player::playerName::JACK, m_levels.at(0));
    m_player_Jill = new Player(Player::playerName::JILL, m_levels.at(0));

    

    //initialize containers according to states
    DashSelectables.push_back(new GameButton("Play", CANVAS_WIDTH * 16 / 17, CANVAS_HEIGHT * 10 / 11, INIT_ROUND));
    DashSelectables.push_back(new HelpButton("Story", CANVAS_WIDTH * 16 / 17, CANVAS_HEIGHT * 8 / 11, CANVAS_WIDTH / 2 - 1.0f, CANVAS_HEIGHT / 2, PAPYRUS_WIDTH, PAPYRUS_HEIGHT));
    DashSelectables.push_back(new MusicButton(CANVAS_WIDTH / 17, CANVAS_HEIGHT / 17));

    MarkCollection.push_back(new Mark(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, MARK_RADIUS, 1));
    MarkCollection.push_back(new Mark(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, MARK_RADIUS, 2));
    MarkCollection.push_back(new Mark(CANVAS_WIDTH * 3 / 4, CANVAS_HEIGHT / 2, MARK_RADIUS, 3));
    //MarkCollection.push_back(new MusicButton(CANVAS_WIDTH / 9, CANVAS_HEIGHT / 9));

    BJSelectables.push_back(new GameButton("Stand", CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, STANDPHASE));
    BJSelectables.push_back(new HelpButton("Help", CANVAS_WIDTH * 10 / 11, CANVAS_HEIGHT / 11, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 4, RULES_WIDTH, RULES_HEIGHT));
    BJSelectables.push_back(new MusicButton(CANVAS_WIDTH / 17, CANVAS_HEIGHT / 17));

    GOSelectables.push_back(new GameButton("Again", CANVAS_WIDTH * 10 / 11, CANVAS_HEIGHT * 3 / 11, LOADING));   
    GOSelectables.push_back(new WindowButton("Exit", CANVAS_WIDTH * 10 / 11, CANVAS_HEIGHT / 11));

    m_winner = nullptr;
    m_active_Mark = nullptr;
    m_active_Card = nullptr;
    m_valid_Action = false;
    m_rounds = 0;

    graphics::preloadBitmaps("assets/");

    return;
}

void Game::togglePlayer()
{
    if (m_active_Player == m_player_Jack)
    {
        m_active_Player = m_player_Jill;
    }
    else
    {
        m_active_Player = m_player_Jack;
    }
}

const Player* Game::player_toStand() const
{
    if (m_player_Standed == 0) //no player has standed
    {
        return m_active_Player == m_player_Jack ? m_player_Jill : m_player_Jack;
    }
    return m_active_Player;
}

void Game::pressEnterMessg(graphics::Brush& br, const bool red) const //modifies br, so reference is not read-only
{
    graphics::setFont("assets/CATChilds.ttf");
    float r = 0.8f * red;
    SET_COLOR(br.fill_color, r, 0.0f, 0.0f);
    graphics::drawText(CANVAS_WIDTH / 8, CANVAS_HEIGHT * 7 / 8, 0.5f, "press  ENTER  to continue", br);
}

void Game::drawBackground(graphics::Brush& br, const std::string& bitmap) const
{
    br.texture = "assets/" + bitmap + ".png";
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

Selectable* const Game::handleSelectables(std::deque<Selectable*>& selectables, graphics::MouseState ms, float mx, float my) const
{

    for (auto sel : selectables)
    {
        bool highlighted = sel->inScope(mx, my);
        sel->setHighlight(highlighted);
    }

    for (auto sel : selectables)
    {

        bool clicked = sel->inScope(mx, my) && ms.button_left_pressed;

        if (clicked)
        {
            sel->onClick();
            return sel;
        }
    }
    return nullptr;
}

void Game::destroy()
{
    //destroying players...
    if (m_player_Jack)
    {
        delete m_player_Jack;
        m_player_Jack = nullptr;
    }
    if (m_player_Jill)
    {
        delete m_player_Jill;
        m_player_Jill = nullptr;
    }

    //destroying levels...
    for (auto lvl : m_levels)
    {
        delete lvl;
    }

    //destroying every selectable...
    for (auto sel : DashSelectables)
    {
        delete sel;
    }
    
    for (auto mark : MarkCollection)
    {
        delete mark;
    }
  
    for (auto sel : BJSelectables)
    {
        delete sel;
    }

    for (auto sel : GOSelectables)
    {
        delete sel;
    }

    m_levels.clear();
    m_events.clear();

    DashSelectables.clear();
    MarkCollection.clear();
    BJSelectables.clear();
    GOSelectables.clear();
    
    Level::reset();
}

Game* Game::m_instance = nullptr;

Game* const Game::getInstance()
{
    if (!m_instance)
    {
        m_instance = new Game();
    }
    return m_instance;
};

Game::~Game()
{
    destroy();
    state_n_music.clear();
}