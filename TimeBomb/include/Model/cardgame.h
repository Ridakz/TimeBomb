#ifndef CARDGAME_H
#define CARDGAME_H

#include "deck.h"
#include "side.h"
#include "move.h"

class CardGame
{
public:

    static const int maxPlayers = 8;
    static const int minPlayers = 4;


    Deck m_deck;
    Card m_playerHands[maxPlayers][5];
    Side m_playerSide [maxPlayers];
    Side m_winner;

    int m_wireCutterId;
    int m_playerCount;
    int m_roundNumber = 1;
    int m_cardPlayedCount = 0;
    int m_defusedCard = 0;
    int m_matchNumber = 0;

    bool m_isGameFinished;

    CardGame(int playerCount);

    void startGame ();

    void hideCards();

    void dealCards();

    void setPlayerSides();

    bool isWinner(int playerId) const;

    void gatherCards ();

    bool canApply (Move move, int playId) const;

    void cardsCount(int id, int cards [3]);

    void applyMove (Move move);

    ~CardGame ();
};

#endif // CARDGAME_H
