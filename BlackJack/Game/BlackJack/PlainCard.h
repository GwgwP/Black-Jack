#pragma once
#include "Card.h"

class PlainCard final :
    public Card
{
    
public:
    enum Ranks {TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN }; 

private:
    const Ranks m_rank;

public:
    PlainCard(const Suits& s, const Ranks& r);
    const uint getValueOfCard() const override;
    void draw() const ;
    ~PlainCard() {};
};