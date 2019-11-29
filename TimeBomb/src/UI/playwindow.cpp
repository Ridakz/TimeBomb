#include "UI/playwindow.h"
#include "UI/customwidget.h"

PlayWindow::PlayWindow()  {
    setupCards();
}

void PlayWindow::revealCard(Move card, Card c) {
    playerCards[card.playerId][card.cardIndex]->reveal(c);
}

void PlayWindow::hideCard(Move card) {
    playerCards[card.playerId][card.cardIndex]->hide();
}

void PlayWindow::updateDefusingNumber(int number) {
    defusingNumber->setText(QString::number(number));
}


void PlayWindow::initGame(const CardGame &cardGame, int myId) {
    showSide(cardGame.m_playerSide[myId]);
    showCards();


    this->gameNumber->setText("Game " + QString::number(cardGame.m_matchNumber));
    defusingNumber->setText("0");
    turnNumber->setText("Turn 1");
    roundNumber->setText("Round 1/4");

    if(myId == cardGame.m_wireCutterId) {
        yourTurn->setVisible(true);
    }
    for(int i = 0; i < 6; ++i) {
        nicknames[i]->setStyleSheet("QLabel { color : black; }");
    }
    nicknames[cardGame.m_wireCutterId]->setStyleSheet("QLabel { color : red; }");
}

void PlayWindow::setupCards() {

    QPixmap pixmap(":/Pictures/Hidden.png");
    QMatrix rot90; rot90.rotate(90);
    auto pixmap2 = pixmap.transformed(rot90);
    QIcon ButtonIcon2(pixmap2);
    QIcon ButtonIcon(pixmap);

    centralWidget = new CustomWidget();
    centralWidget->setMouseTracking(true);

    name = new QLabel(centralWidget);

    for(int i = 0; i < 5 ;++i) {
        int deltaPixel = i * 70;
        playerCards[0][i] = new PlayerCard(centralWidget,Move{0,i},0);
        playerCards[0][i]->setGeometry(QRect(170+deltaPixel, 20, 61, 101));
        playerCards[0][i]->setIcon(ButtonIcon);
        playerCards[0][i]->setIconSize(pixmap.rect().size());
    }

    for(int i = 0; i < 5 ;++i) {
        int deltaPixel = i * 70;
        playerCards[1][i] = new PlayerCard(centralWidget,Move{1,i},0);
        playerCards[1][i]->setGeometry(QRect(590+deltaPixel, 20, 61, 101));
        playerCards[1][i]->setIcon(ButtonIcon);
        playerCards[1][i]->setIconSize(pixmap.rect().size());
    }

    for(int i=0 ; i < 5; ++i) {
        int deltaPixel = i * 70;
        playerCards[2][i] = new PlayerCard(centralWidget,Move{2,i},270);
        playerCards[2][i]->setGeometry(QRect(1050, 160+deltaPixel, 101, 61));
        playerCards[2][i]->setIcon(ButtonIcon2);
        playerCards[2][i]->setIconSize(pixmap2.rect().size());
    }

    for(int i = 0; i < 5 ;++i) {
        int deltaPixel = i * 70;
        playerCards[3][i] = new PlayerCard(centralWidget,Move{3,i},0);
        playerCards[3][i]->setGeometry(QRect(590+deltaPixel, 530, 61, 101));
        playerCards[3][i]->setIcon(ButtonIcon);
        playerCards[3][i]->setIconSize(pixmap.rect().size());
    }

    for(int i = 0; i < 5 ;++i) {
        int deltaPixel = i * 70;
        playerCards[4][i] = new PlayerCard(centralWidget,Move{4,i},0);
        playerCards[4][i]->setGeometry(QRect(170 + deltaPixel, 530, 61, 101));
        playerCards[4][i]->setIcon(ButtonIcon);
        playerCards[4][i]->setIconSize(pixmap.rect().size());
    }

    for(int i = 0; i < 5 ;++i) {
        int deltaPixel = i * 70;
        playerCards[5][i] = new PlayerCard(centralWidget,Move{5,i},90);
        playerCards[5][i]->setGeometry(QRect(10, 160 + deltaPixel, 101, 61));
        playerCards[5][i]->setIcon(ButtonIcon2);
        playerCards[5][i]->setIconSize(pixmap2.rect().size());
    }

    for(int i = 0; i < 6 ; ++i) {
        auto geo0 = playerCards[i][0]->geometry();
        auto geo2 = playerCards[i][2]->geometry();
        auto geo3 = playerCards[i][3]->geometry();
        playerCards[i][0]->setGeometry(geo2);
        playerCards[i][2]->setGeometry(geo3);
        playerCards[i][3]->setGeometry(geo0);
    }


    QPixmap defusedPm(":/Pictures/Defusing.png");
    QIcon defusedIcon(defusedPm);

    defusingImage = new QLabel(centralWidget);
    defusingImage->setGeometry(QRect(530, 250, 61, 101));
    defusingImage->setPixmap(defusedPm);

    QColor red (189, 51, 51);
    QColor brown(168,121,50);
    QColor green(17, 240, 50);

    defusingNumber = new QLabel(centralWidget);
    defusingNumber->setGeometry(QRect(530, 310, 61, 101));
    defusingNumber->setAlignment(Qt::AlignCenter);
    defusingNumber->setText("0");
    auto font = defusingNumber->font();
    font.setBold(true);
    font.setPointSize(16);
    defusingNumber->setFont(font);

    yourTurn = new QLabel(centralWidget);
    yourTurn->setText("YOUR TURN");
    yourTurn->setGeometry(QRect(500, 350, 140, 101));
    yourTurn->setVisible(false);
    yourTurn->setFont(font);
    yourTurn->setAlignment(Qt::AlignCenter);

    QFont font1;
    font1.setPointSize(12);
    font1.setBold(true);
    font1.setWeight(75);
    QString namesStr[] = {"Cheng","Rachel","Hans","Nina","Alex","Lisa"};

    for(int i =0; i < 6 ; ++i) {
        nicknames[i] = new QLabel(centralWidget);
        nicknames[i]->setFont(font);
        nicknames[i]->setAlignment(Qt::AlignCenter);
        nicknames[i]->setText(namesStr[i]);
    }

    nicknames[0]->setGeometry(QRect(270, 130, 141, 31));
    nicknames[1]->setGeometry(QRect(690, 130, 141, 31));
    nicknames[2]->setGeometry(QRect(970, 300, 61, 61));
    nicknames[3]->setGeometry(QRect(690, 490, 141, 31));
    nicknames[4]->setGeometry(QRect(270, 490, 141, 31));
    nicknames[5]->setGeometry(QRect(120, 300, 61, 61));


    gameNumber = new QLabel(centralWidget);
    gameNumber->setGeometry(QRect(30, 30, 104, 31));
    font1.setPointSize(16);
    font1.setBold(true);
    font1.setWeight(75);
    gameNumber->setFont(font1);

    roundNumber = new QLabel(centralWidget);
    roundNumber->setGeometry(QRect(490, 160, 131, 21));
    roundNumber->setFont(font1);
    roundNumber->setAlignment(Qt::AlignCenter);

    turnNumber = new QLabel(centralWidget);
    turnNumber->setGeometry(QRect(510, 190, 91, 21));
    turnNumber->setFont(font1);
    turnNumber->setAlignment(Qt::AlignCenter);


    gameNumber->setText("Game 1");
    roundNumber->setText("Round 1/4");
    turnNumber->setText("Turn 1");


    QWidget *widget = new QWidget(centralWidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(500, 440, 121, 71));
    QVBoxLayout *infoLayout = new QVBoxLayout(widget);
    infoLayout->setSpacing(1);
    infoLayout->setContentsMargins(11, 11, 11, 11);
    infoLayout->setObjectName(QString::fromUtf8("infoLayout"));
    infoLayout->setContentsMargins(0, 0, 0, 0);

    sideLabel = new QLabel(widget);
    sideLabel->setObjectName(QString::fromUtf8("sideLabel"));
    sideLabel->setFont(font);
    sideLabel->setAlignment(Qt::AlignCenter);

    infoLayout->addWidget(sideLabel, 0, Qt::AlignHCenter);

    name = new QLabel(widget);
    name->setObjectName(QString::fromUtf8("name"));
    name->setMinimumSize(QSize(95, 24));
    name->setMaximumSize(QSize(95, 24));
    name->setFont(font);
    name->setAlignment(Qt::AlignCenter);

    infoLayout->addWidget(name, 0, Qt::AlignHCenter);

    QHBoxLayout *countHLayout = new QHBoxLayout();
    countHLayout->setSpacing(6);
    countHLayout->setObjectName(QString::fromUtf8("countHLayout"));
    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    countHLayout->addItem(horizontalSpacer);

    playerDefusings = new QLabel(widget);
    playerDefusings->setObjectName(QString::fromUtf8("playerDefusings"));
    playerDefusings->setFont(font);
    playerDefusings->setAlignment(Qt::AlignCenter);

    countHLayout->addWidget(playerDefusings);

    playerNeutrals = new QLabel(widget);
    playerNeutrals->setObjectName(QString::fromUtf8("playerNeutrals"));
    playerNeutrals->setFont(font);
    playerNeutrals->setAlignment(Qt::AlignCenter);

    countHLayout->addWidget(playerNeutrals);


    playerBomb = new QLabel(widget);
    playerBomb->setObjectName(QString::fromUtf8("defusingCount"));
    playerBomb->setFont(font);
    playerBomb->setAlignment(Qt::AlignCenter);

    playerBomb->setStyleSheet("QLabel { color : red; }");
    playerNeutrals->setStyleSheet("QLabel { color : peru; }");
    playerDefusings->setStyleSheet("QLabel { color : blue; }");


    countHLayout->addWidget(playerBomb);

    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    countHLayout->addItem(horizontalSpacer_2);

    infoLayout->addLayout(countHLayout);

    // score

    scoreList = new QGroupBox(centralWidget);
    scoreList->setObjectName(QString::fromUtf8("ScoreList"));
    scoreList->setGeometry(QRect(970, 10, 181, 140));
    scoreList->setMaximumSize(QSize(181, 140));
    scoreList->setAutoFillBackground(false);
    scoreList->setFlat(false);
    formLayout = new QFormLayout(scoreList);
    formLayout->setSpacing(6);
    formLayout->setContentsMargins(11, 11, 11, 11);
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    QFont font2;
    font2.setPointSize(11);
    font2.setBold(true);
    font2.setWeight(75);

    for(int i = 0; i< 6 ; ++i) {
        scores[i][0] = new QLabel(scoreList);
        scores[i][0]->setFont(font2);
        scores[i][0]->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scores[i][0]->setText(nicknames[i]->text());

        scores[i][1] = new QLabel(scoreList);
        scores[i][1]->setFont(font2);
        scores[i][1]->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scores[i][1]->setText("0");
        formLayout->setWidget(i, QFormLayout::LabelRole, scores[i][0]);
        formLayout->setWidget(i, QFormLayout::FieldRole, scores[i][1]);
    }

    QPixmap wire (":/Pictures/WireCutter2.png");
    wirePicture = new QLabel(centralWidget);
    wire = wire.scaled(64,64);
    wirePicture->setPixmap(wire);
    wirePicture->setGeometry(QCursor::pos().x(),QCursor::pos().y(),64,64);
    wirePicture->setHidden(true);

    wireCursor = new QCursor (wire,55,32);

    wirePlayerName = new QLabel(centralWidget);
    font1.setBold(true); font1.setPointSize(14);
    wirePlayerName->setFont(font1);

    winnerMessage = new QLabel(centralWidget);
    font1.setPointSize(12);
    winnerMessage->setFont(font1);
    winnerMessage->setGeometry(QRect(180, 250, 200, 71));

    //centralWidget->setCursor(*wireCursor);
    centralWidget->setEnabled(true);


    //QApplication::setOverrideCursor(*wireCursor);
}

void PlayWindow::showName(int id) {
    QString namesStr[] = {"Cheng","Rachel","Hans","Nina","Alex","Lisa"};
    QFont font1;
    font1.setPointSize(16);
    font1.setBold(true);
    name->setFont(font1);
    name->setAlignment(Qt::AlignCenter);
    name->setText(namesStr[id]);
    name->setGeometry(QRect(510,375,100,150));
    name->setVisible(true);
}

void PlayWindow::switchCutter(int previous, int next) {
    nicknames[next]->setStyleSheet("QLabel { color : red; }");
    nicknames[previous]->setStyleSheet("QLabel { color : black; }");
}

void PlayWindow::showSide(Side side) {
    if(side == Terrorist) {
        sideLabel->setStyleSheet("QLabel { color : red; }");
        sideLabel->setText("Terrorist");
    }
    else {
        sideLabel->setStyleSheet("QLabel { color : blue;}");
        sideLabel->setText("Sherlock");
    }
}

void PlayWindow::showCardNumber(int neutrals, int defusing, int bomb) {
    playerNeutrals->setText(QString::number(neutrals));
    playerDefusings->setText(QString::number(defusing));
    playerBomb->setText(QString::number(bomb));
}

void PlayWindow::showCards() {
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 5; ++j) {
            playerCards[i][j]->setVisible(true);
            playerCards[i][j]->hide();
        }
    }
}


void PlayWindow::showNextRound(int roundNumber) {

    this->roundNumber->setText("Round "+ QString::number(roundNumber) + "/4");

    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6-roundNumber; ++j) {
            playerCards[i][j]->hide();
        }
        playerCards[i][6-roundNumber]->setVisible(false);
    }
}

PlayWindow::~PlayWindow() {
    delete centralWidget;
    delete wireCursor;
}
