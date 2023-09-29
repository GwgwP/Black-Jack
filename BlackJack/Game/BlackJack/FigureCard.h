#pragma once
#include "Card.h"
#include "defines.h"

class FigureCard final :
    public Card
{
public:
    enum Ranks {JACK=11, QUEEN, KING };

protected:
    const Ranks m_rank;

public:
    FigureCard(const Suits& s, const Ranks& r);
    const uint getValueOfCard() const override;
    void draw() const override;
   
    ~FigureCard() {};
};