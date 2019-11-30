#include "UI/playercard.h"
#include <QSound>



PlayerCard::PlayerCard(QWidget *widget, Move m, int rot) : QPushButton(widget), m_card(m), m_rotation(rot) {}

void PlayerCard::mousePressEvent(QMouseEvent *e) {
    emit cardClicked(m_card);
}

void PlayerCard::hide() {
    QPixmap pixmap;
    QMatrix rot;
    rot.rotate(m_rotation);
    pixmap.load(":/Pictures/Hidden.png");
    pixmap = pixmap.transformed(rot);
    setIcon(QIcon(pixmap));
}

void PlayerCard::reveal(Card c) {
    QPixmap pixmap;
    QMatrix rot;
    rot.rotate(m_rotation);

    QIcon ButtonIcon(pixmap);
    switch (c.m_value) {
    case Card::Bomb:
        pixmap.load(":/Pictures/Bomb.png");
        pixmap = pixmap.transformed(rot);
        setIcon(QIcon(pixmap));
        QSound::play(":sounds/156031__iwiploppenisse__explosion.wav");
        break;
    case Card::Defusing:
        pixmap.load(":/Pictures/Defusing.png");
        pixmap = pixmap.transformed(rot);
        setIcon(QIcon(pixmap));
        QSound::play(":sounds/37786__the-bizniss__pliers.wav");
        break;
    case Card::Neutral :
        pixmap.load(":/Pictures/Neutral.png");
        pixmap = pixmap.transformed(rot);
        setIcon(QIcon(pixmap));

        break;
    }
}

PlayerCard::~PlayerCard() {}

