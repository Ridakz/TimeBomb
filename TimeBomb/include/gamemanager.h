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

    GameManager(int playerCount);
    GameManager(ClientWindow *client);



    void initGame();

    void addWinnerScore();
    void showWinners();


    void showCardNumber();

    void updateScore();
    void connectCardClickedSend();
    void connectCardClickedApply();

    void debugShowAll();    
    void showToolTip();


virtual ~GameManager();


public slots:
    void sendIfMyTurn(Move move);

    void updateCursorPos(int x, int y);

    void showNextRound();

    void receiveGameInform(unsigned int seed, int clientCount, int clientId);


    void applyMove (Move move);

    void sendCursorPos();

    void cardEntered(Move move);
    void cardLeft(Move move);
    void connectCardHover();

private:
    Player* m_players[8];
    CardGame *m_cardGame;
    PlayWindow * m_GUI;
    ClientWindow* m_client;
    bool m_isGamePaused = false;
    int m_id;
};

#endif // GAMEMANAGER_H
