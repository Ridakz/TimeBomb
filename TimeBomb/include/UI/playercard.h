#ifndef PLAYERCARD_H
#define PLAYERCARD_H
#include "Model/move.h"
#include "Model/card.h"
#include <QtWidgets/QPushButton>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QDebug>

#include <chrono>
#include <thread>
#include "server.h"


class PlayerCard : public QPushButton
{

Q_OBJECT


public:
    Move m_card;
    int m_rotation;

    PlayerCard(QWidget* widget, Move m, int rot);

    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void hide();
    void hover();

    void reveal(Card c);

    virtual ~PlayerCard();

signals :
    void cardClicked(Move card);
    void cardOnEnter(Move card);
    void cardOnLeave(Move card);

};

#endif // PLAYERCARD_H
