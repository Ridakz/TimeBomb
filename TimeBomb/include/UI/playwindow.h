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

    QString STYLE_CURRENT_USER = "QLabel { color : rgba(0,0,255,0.7); border: 1px solid rgba(100, 100, 100, 1); border-radius: 4px; }";
    QString STYLE_USER = "QLabel { color : white; }";
    QString STYLE_SCORE = "QLabel { color : white; }";
    QString STYLE_PLAYER_BOMB = "QLabel { color : red; }";
    QString STYLE_PLAYER_NEUTRAL = "QLabel { color : peru; }";
    QString STYLE_PLAYER_DEFUSER = "QLabel { color : blue; }";



};

#endif // PLAYWINDOW_H
