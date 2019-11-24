#ifndef BOTPLAYER_H
#define BOTPLAYER_H
#include "player.h"
#include <QObject>

class BotPlayer :  public QObject,public Player
{
Q_OBJECT
public:
    BotPlayer(int id);

    void chooseMove(const CardGame& cardGames);
signals:
    void botPlayed(Move m);

private :
    Move m_move;
};

#endif // BOTPLAYER_H
