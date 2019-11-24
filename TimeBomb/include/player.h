#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Model/cardgame.h"


class Player
{

public:
    Player(int i);

    virtual void chooseMove(const CardGame& cardGames) = 0;
    int m_score;
    int m_id;
    virtual ~Player();

};

#endif // PLAYER_H
