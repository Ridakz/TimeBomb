#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "Model/cardgame.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(int id);

    void chooseMove(const CardGame& cardGame) {
        //do nothing, move is sent from UI pressed to server
    }
};

#endif // HUMANPLAYER_H
