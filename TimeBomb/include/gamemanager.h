#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QThread>
#include <QObject>

#include "Model/cardgame.h"
#include "player.h"
#include "Model/deck.h"
#include "Model/move.h"
#include "Model/side.h"
#include "UI/playwindow.h"
#include "UI/clientwindow.h"

class GameManager : public QObject {
    Q_OBJECT

public:
    GameManager();

    GameManager(int playerCount, PlayWindow* UI, ClientWindow* client);
    GameManager(int playerCount, PlayWindow* UI);


    void initGame();

    void addWinnerScore();
    void showWinners();


    void showCardNumber();

    void updateScore();
    void connectCardClickedSend();
    void connectCardClickedApply();

    void debugShowAll();

virtual ~GameManager();


public slots:
    void showNextRound();

    void receiveGameInform(unsigned int seed, int clientCount, int clientId);

    void sendIfMyTurn(Move move);

    void applyMove (Move move);

private:
    Player* m_players[8];
    CardGame m_cardGame;
    PlayWindow * m_GUI;
    ClientWindow* m_client;
    bool m_isGamePaused = false;
    int m_id;
};

#endif // GAMEMANAGER_H
