#pragma once
#include "Card.h"

class AceCard final :
    public Card
{
public:
    enum Ranks { ACE=1 };
  
private:
    const Ranks m_rank = Ranks::ACE;    
    bool m_asOne = false;       //at first let the value be 11

public:
    AceCard(const Suits& s);

    void setAsOne(const bool asOne);
    const uint getValueOfCard() const override;
    
    void draw() const override;
    ~AceCard() {};
};