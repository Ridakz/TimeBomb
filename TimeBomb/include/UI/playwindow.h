#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QFormLayout>
#include <QGroupBox>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QTimer>
#include "Model/cardgame.h"
#include "Model/side.h"
#include "playercard.h"
#include "vector"

class PlayWindow
{


public:

    PlayWindow();

    void revealCard (Move card, Card c);

    void hideCard (Move card);

    void updateDefusingNumber (int number);

    void setupCards ();

    void initGame(const CardGame& cardGame,int myId);

    void showName(int id);

    void switchCutter(int previous, int next);

    void showSide(Side side);

    void showCardNumber (int neutrals, int defusing, int bomb);

    void showCards();

    void showNextRound(int roundNumber);

    virtual ~PlayWindow();

    PlayerCard* playerCards [6][5];
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QLabel *defusingImage, *defusingNumber;
    QLabel* yourTurn;
    QLabel* winnerMessage;
    QLabel* playerNeutrals, *playerDefusings,*playerBomb;
    QLabel* name;
    QLabel* sideLabel;
    QLabel* nicknames[6];
    QLabel* scores[6][2];
    QPalette palette;


    QLabel* gameNumber;
    QLabel* turnNumber;
    QLabel* roundNumber;

    QGroupBox *scoreList;
    QFormLayout* formLayout;

    // invisible cursor + wire picture when its not client turn
    QLabel*  wirePicture;
    QLabel*  wirePlayerName;
    QCursor* invisibleCursor;

    // real wire cursor used when its client turn
    QCursor* wireCursor;
};

#endif // PLAYWINDOW_H
