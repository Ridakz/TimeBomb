#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck
{
public:
    Deck();
    void init (int playerCount);
    void shuffle();
    void remove(Card c);
    std::vector<Card> cards;
};

#endif // DECK_H
