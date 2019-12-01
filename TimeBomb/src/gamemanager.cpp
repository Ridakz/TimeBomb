#include "gamemanager.h"
#include "botplayer.h"
#include "humanplayer.h"
#include <iterator>
#include <QMessageBox>

GameManager::GameManager(ClientWindow* client) :
             QObject(), m_client(client)
{
    QObject::connect(client,&ClientWindow::receivedMove,this,&GameManager::applyMove);
    QObject::connect(client,&ClientWindow::receivedSizeAndIndex,this,&GameManager::receiveGameInform);
    QObject::connect(client,&ClientWindow::receivedCursorPos,this,&GameManager::updateCursorPos);
    m_players[0] = nullptr;
}

GameManager::GameManager(int playerCount) :
             QObject(), m_cardGame(new CardGame(playerCount)), m_GUI(new PlayWindow(playerCount))
{
    connectCardHover();
    connectCardClickedApply();
    m_players[0] = new HumanPlayer(0);
    m_client = nullptr;

    srand(time(nullptr));
    m_id = 0;

    for (int i = 1; i < playerCount; ++i) {
        BotPlayer * bot = new BotPlayer(i);
        m_players[i] = bot;
        QObject::connect(bot,&BotPlayer::botPlayed,this,&GameManager::applyMove);
    }

    m_GUI->centralWidget->show();
    m_GUI->showName(m_id);
    initGame();
}

void GameManager::showToolTip() {
    int T[3] = {0,0,0};
    for(int i =0; i<m_cardGame->m_playerCount;++i) {
        for(int j = 0; j < 6 - m_cardGame->m_roundNumber ; ++j) {
            m_GUI->playerCards[i][j]->setToolTip(QString::number(m_cardGame->m_playerHands[i][j].m_value) + "  card#"
                                                 + QString::number(m_GUI->playerCards[i][j]->m_card.cardIndex));
            T[m_cardGame->m_playerHands[i][j].m_value]++;
        }
    }
    qDebug() << "Bombs : " << T[1] << " Defusing " << T[2] + m_cardGame->m_defusedCard;
}

void GameManager::initGame() {
    m_cardGame->startGame();
    m_GUI->initGame(*m_cardGame,m_id);
    showNextRound();
    m_isGamePaused = false;
    showToolTip();
    m_players[m_cardGame->m_wireCutterId]->chooseMove(*m_cardGame);

    if(m_id == m_cardGame->m_wireCutterId) {
        m_GUI->wirePicture->setHidden(true);
        m_GUI->wirePlayerName->setHidden(true);
        m_GUI->centralWidget->setCursor(*m_GUI->wireCursor);
        m_GUI->yourTurn->setVisible(true);
    }
    else {
    }

    m_GUI->wirePlayerName->setText(m_GUI->nicknames[m_cardGame->m_wireCutterId]->text());
}

void GameManager::addWinnerScore() {
    for(int i = 0; i < m_cardGame->m_playerCount ; ++i) {
        if(m_cardGame->isWinner(i)) {
            ++(m_players[i]->m_score);
        }
    }
}

void GameManager::showWinners() {
    int terrorist[2];
    int index = 0;
    for(int i = 0;i < m_cardGame->m_playerCount; ++i) {
        if(m_cardGame->isWinner(i)) {
            terrorist[index++] = i;
        }
    }

    m_GUI->winnerMessage->show();
    if(m_cardGame->m_winner == Terrorist) {
        m_GUI->winnerMessage->setText("<font color=\"red\">Terrorist Team Wins</font><br><font color=\"black\">\n "
                                      "Terrorists : " + m_GUI->nicknames[terrorist[0]]->text() + " " + m_GUI->nicknames[terrorist[1]]->text() + " </font>");
    }
    else {
        m_GUI->winnerMessage->setText("<font color=\"blue\">Sherlock Team Wins</font><br><font color=\"black\">\nTerrorists : " +
                       m_GUI->nicknames[terrorist[0]]->text() + " " + m_GUI->nicknames[terrorist[1]]->text() + " </font>");
    }
    QTimer::singleShot(4000,this,[this]() {
        m_GUI->winnerMessage->hide();
    });
}

void GameManager::debugShowAll() {
    for(int i = 0; i < m_cardGame->m_playerCount; ++i) {
        for(int j = 0; j < 6 - m_cardGame->m_roundNumber; ++j) {
            m_GUI->playerCards[i][j]->setVisible(true);
            m_GUI->playerCards[i][j]->reveal(m_cardGame->m_playerHands[i][j].m_value);
        }
    }
}

void GameManager::connectCardClickedApply() {
    for(int i= 0; i< m_cardGame->m_playerCount; ++i) {
        for(int k = 0; k < 5; ++k) {
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardClicked,this,[this](Move m) {
                if(!m_isGamePaused && m_cardGame->canApply(m,m_id)) {
                        this->applyMove(m);
                }
            });
        }
    }
}

void GameManager::connectCardClickedSend() {
    for(int i= 0; i< m_cardGame->m_playerCount; ++i) {
        for(int k = 0; k < 5; ++k) {
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardClicked,this,&GameManager::sendIfMyTurn);
        }
    }
}

void GameManager::connectCardHover() {
    for(int i= 0; i< m_cardGame->m_playerCount; ++i) {
        for(int k = 0; k < 5; ++k) {
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardOnEnter,this,&GameManager::cardEntered);
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardOnLeave,this,&GameManager::cardLeft);
        }
    }
}

void GameManager::showNextRound() {
    int cardCount[3];
    m_cardGame->cardsCount(m_id,cardCount);
    m_GUI->showCardNumber(cardCount[0],cardCount[1],cardCount[2]);
}

void GameManager::receiveGameInform(unsigned int seed, int clientCount, int clientId) {
    srand(seed);
    m_id = clientId;
    qDebug() << "RECEIVED : PLAYER INDEX";
    for(int i = 0; i < clientCount; ++i) {
        m_players[i] = new HumanPlayer(i);
    }

    int playerCount = std::max(clientCount,4);
    m_cardGame = new CardGame(playerCount);
    m_GUI = new PlayWindow(playerCount);
    connectCardHover();


    connectCardClickedSend();
    for (int i = clientCount; i < 4; ++i) {
        BotPlayer * bot = new BotPlayer(i);
        m_players[i] = bot;
        QObject::connect(bot,&BotPlayer::botPlayed,this,&GameManager::applyMove);
    }
    if(m_id == m_cardGame->m_wireCutterId) {
        m_GUI->yourTurn->setVisible(true);
    }
    m_GUI->centralWidget->show();
    m_GUI->showName(m_id);
    initGame();

    QTimer* timedCursorUpdate = new QTimer();
    QObject::connect(timedCursorUpdate,&QTimer::timeout,this,&GameManager::sendCursorPos);
    timedCursorUpdate->setInterval(100);
    timedCursorUpdate->start();
}

void GameManager::cardEntered(Move move) {
    if(!m_cardGame->m_playerHands[move.playerId][move.cardIndex].m_isRevealed) {
        m_GUI->playerCards[move.playerId][move.cardIndex]->hover();
    }
}

void GameManager::cardLeft(Move move) {
    if(!m_cardGame->m_playerHands[move.playerId][move.cardIndex].m_isRevealed) {
        m_GUI->playerCards[move.playerId][move.cardIndex]->hide();
    }
}

void GameManager::sendIfMyTurn(Move move) {
    if(!m_isGamePaused && m_cardGame->canApply(move,m_id)) {
        qDebug() << "SENT: CARD";
        m_client->sendMove(move.playerId,move.cardIndex);
    }
}

void GameManager::sendCursorPos()
{
    bool isMyTurn = m_id == m_cardGame->m_wireCutterId;
    int x = m_GUI->centralWidget->mapFromGlobal(this->m_GUI->wireCursor->pos()).x();
    int y = m_GUI->centralWidget->mapFromGlobal(this->m_GUI->wireCursor->pos()).y();
    if(isMyTurn && y >= 0 && x >= 0) {
        m_client->sendCursorPosition(std::max(x-55,0),std::max(y-32,0));
    }
}

void GameManager::updateCursorPos(int x, int y) {
    m_GUI->wirePlayerName->setGeometry(x,y+40,100,50);
   if(m_cardGame->m_wireCutterId != m_id) {
       m_GUI->wirePicture->setHidden(false);
       m_GUI->wirePicture->setGeometry(x,y,64,64);
   }
}

void GameManager::updateScore() {
    std::vector<Player*> p;
    for(int i = 0; i < m_cardGame->m_playerCount; ++i) {
        p.push_back(m_players[i]);
    }
    std::sort(p.begin(),p.end(),[](const Player* a, const Player* b) -> bool {return a->m_score > b->m_score ;});
    for(int i = 0; i < m_cardGame->m_playerCount; ++i) {
        m_GUI->scores[i][0]->setText(m_GUI->nicknames[p[i]->m_id]->text());
        m_GUI->scores[i][1]->setText(QString::number(p[i]->m_score));
    }
}

void GameManager::applyMove(Move move) {
    //debugShowAll();
    m_isGamePaused = true;
    m_GUI->switchCutter(m_cardGame->m_wireCutterId,move.playerId);
    m_GUI->revealCard(move, m_cardGame->m_playerHands[move.playerId][move.cardIndex]);
    m_cardGame->applyMove(move);
    m_GUI->wirePlayerName->setText(m_GUI->nicknames[m_cardGame->m_wireCutterId]->text());
    m_GUI->updateDefusingNumber(m_cardGame->m_defusedCard);
    m_GUI->yourTurn->setVisible(false);
    m_GUI->centralWidget->setCursor(QCursor());
    m_GUI->wirePlayerName->setHidden(false);

    // wait and start new game
    if(m_cardGame->m_isGameFinished) {
        //debugShowAll();
        addWinnerScore();
        updateScore();
        QApplication::processEvents();
        QApplication::processEvents();
        showWinners();
        QTimer::singleShot(5000,this,[this](){initGame();});
        return;
    }


    bool isMyTurn = m_id == m_cardGame->m_wireCutterId;
    if(isMyTurn) {
        m_GUI->wirePlayerName->setHidden(true);
        m_GUI->yourTurn->setVisible(true);
        //QApplication::setOverrideCursor(*m_GUI->wireCursor);
        m_GUI->centralWidget->setCursor(*m_GUI->wireCursor);
        m_GUI->wirePicture->setHidden(true);
    }

    bool isEndOfRound = m_cardGame->m_cardPlayedCount == 0;
    if(isEndOfRound) {
        QTimer::singleShot(3000,this,[this](){
            showToolTip();
            m_GUI->showNextRound(m_cardGame->m_roundNumber);
            showNextRound();
            m_GUI->turnNumber->setText("Turn " + QString::number(m_cardGame->m_cardPlayedCount+1) + "/" + QString::number(m_cardGame->m_playerCount));
            m_players[m_cardGame->m_wireCutterId]->chooseMove(*m_cardGame);
            m_isGamePaused = false;
        });
    }
    else {
        m_GUI->turnNumber->setText("Turn " + QString::number(m_cardGame->m_cardPlayedCount+1) + "/" + QString::number(m_cardGame->m_playerCount));
        QCoreApplication::processEvents();
        m_players[m_cardGame->m_wireCutterId]->chooseMove(*m_cardGame);
        m_isGamePaused = false;
    }
}

GameManager::~GameManager() {
    if(m_cardGame != nullptr) {
        delete m_cardGame;
    }
    if(m_client != nullptr) {
        delete m_client->m_socket;
        delete m_client;
    }
    if(m_players[0] != nullptr) {
        for(int i = 0; i < m_cardGame->m_playerCount ; ++i) {
            delete m_players[i];
        }
    }
}
