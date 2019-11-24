#include "botplayer.h"
#include <QTimer>

BotPlayer::BotPlayer(int id) :  QObject(), Player (id)
{

}

void BotPlayer::chooseMove(const CardGame &cardGames) {
    std::vector<Move> possibleMoves;
    for(int i = 0; i < cardGames.m_playerCount; ++i) {
        for(int j = 0; j < 6 - cardGames.m_roundNumber; ++j) {
            if(cardGames.canApply(Move{i,j},m_id)) {
                possibleMoves.push_back(Move{i,j});
            }
        }
    }
    m_move = possibleMoves[rand()%possibleMoves.size()];
    QTimer::singleShot(1000,[this]{
        emit botPlayed(m_move);
        //players[m_cardGame.m_wireCutterId]->chooseMove(m_cardGame);
    });
}

