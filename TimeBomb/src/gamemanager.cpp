#include "gamemanager.h"
#include "botplayer.h"
#include "humanplayer.h"
#include <iterator>
#include <QMessageBox>
#include <QDesktopWidget>

GameManager::GameManager(int playerCount, PlayWindow *UI, ClientWindow* client) :
             QObject(), m_cardGame(playerCount), m_client(client), m_GUI(UI)
{
    connectCardClickedSend();
    QObject::connect(client,&ClientWindow::receivedMove,this,&GameManager::applyMove);
    QObject::connect(client,&ClientWindow::receivedSizeAndIndex,this,&GameManager::receiveGameInform);
    m_players[0] = nullptr;
}

GameManager::GameManager(int playerCount, PlayWindow *UI) :
             QObject(), m_cardGame(playerCount), m_GUI(UI)
{
    connectCardClickedApply();
    m_players[0] = nullptr;
    m_client = nullptr;
    receiveGameInform(time(nullptr),1,0);
    m_GUI->centralWidget->setStyleSheet(STYLE_BACKGROUND_IMG);
    //todo : https://stackoverflow.com/questions/5513060/qt-4-move-window-without-title-bar
    m_GUI->centralWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    int x = (screenWidth - WIDTH) / 2;
    int y = (screenHeight - HEIGHT) / 2;

    m_GUI->centralWidget->move( x, y );

    m_GUI->centralWidget->show();
}

void GameManager::initGame() {
    m_cardGame.startGame();
    m_GUI->initGame(m_cardGame,m_id);
    showNextRound();
    m_isGamePaused = false;
    m_players[m_cardGame.m_wireCutterId]->chooseMove(m_cardGame);
    //debugShowAll();
}

void GameManager::addWinnerScore() {
    for(int i = 0; i < m_cardGame.m_playerCount ; ++i) {
        if(m_cardGame.isWinner(i)) {
            ++(m_players[i]->m_score);
        }
    }
}

void GameManager::showWinners() {
    int terrorist[2];
    int index = 0;
    for(int i = 0;i < m_cardGame.m_playerCount; ++i) {
        if(m_cardGame.isWinner(i)) {
            terrorist[index++] = i;
        }
    }
    QMessageBox msgBox ;
    if(m_cardGame.m_winner == Terrorist) {
        msgBox.setText("<font color=\"red\">Terrorist Team Wins</font>\n<font color=\"black\">\nTerrorists : " +
                       m_GUI->nicknames[terrorist[0]]->text() + " " + m_GUI->nicknames[terrorist[1]]->text() + " </font>");
    }
    else {
        msgBox.setText("<font color=\"blue\">Sherlock Team Wins</font>\n<font color=\"black\">\nTerrorists : " +
                       m_GUI->nicknames[terrorist[0]]->text() + " " + m_GUI->nicknames[terrorist[1]]->text() + " </font>");
    }
    msgBox.exec();
}

void GameManager::debugShowAll() {
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6-m_cardGame.m_roundNumber; ++j) {
            m_GUI->playerCards[i][j]->setVisible(true);
            m_GUI->playerCards[i][j]->reveal(m_cardGame.m_playerHands[i][j].m_value);
        }
    }
}

void GameManager::connectCardClickedApply() {
    for(int i= 0; i< 6; ++i) {
        for(int k = 0; k < 5; ++k) {
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardClicked,this,[this](Move m) {
                if(!m_isGamePaused && m_cardGame.canApply(m,m_id)) {
                        this->applyMove(m);
                }
            });
        }
    }
}

void GameManager::connectCardClickedSend() {
    for(int i= 0; i< 6; ++i) {
        for(int k = 0; k < 5; ++k) {
            QObject::connect(m_GUI->playerCards[i][k],&PlayerCard::cardClicked,this,&GameManager::sendIfMyTurn);
        }
    }
}

void GameManager::showNextRound() {
    int cardCount[3];
    m_cardGame.cardsCount(m_id,cardCount);
    m_GUI->showCardNumber(cardCount[0],cardCount[1],cardCount[2]);
}

void GameManager::receiveGameInform(unsigned int seed, int clientCount, int clientId) {
    srand(seed);
    m_id = clientId;
    qDebug() << "RECEIVED : PLAYER INDEX";
    for(int i = 0; i < clientCount; ++i) {
        m_players[i] = new HumanPlayer(i);
    }
    for (int i = clientCount; i < m_cardGame.m_playerCount; ++i) {
        BotPlayer * bot = new BotPlayer(i);
        m_players[i] = bot;
        QObject::connect(bot,&BotPlayer::botPlayed,this,&GameManager::applyMove);
    }
    if(m_id == m_cardGame.m_wireCutterId) {
        m_GUI->yourTurn->setVisible(true);
    }
    m_GUI->centralWidget->show();
    m_GUI->showName(m_id);
    initGame();
}

void GameManager::sendIfMyTurn(Move move) {
    if(!m_isGamePaused && m_cardGame.canApply(move,m_id)) {
        qDebug() << "SENT: CARD";
        m_client->sendMove(move.playerId,move.cardIndex);
    }
}

void GameManager::updateScore() {
    std::vector<Player*> p;
    for(int i = 0; i < m_cardGame.m_playerCount; ++i) {
        p.push_back(m_players[i]);
    }
    std::sort(p.begin(),p.end(),[](const Player* a, const Player* b) -> bool {return a->m_score > b->m_score ;});
    for(int i = 0; i < m_cardGame.m_playerCount; ++i) {
        m_GUI->scores[i][0]->setText(m_GUI->nicknames[p[i]->m_id]->text());
        m_GUI->scores[i][1]->setText(QString::number(p[i]->m_score));
    }

}

void GameManager::applyMove(Move move) {
    //debugShowAll();
    m_isGamePaused = true;
    m_GUI->switchCutter(m_cardGame.m_wireCutterId,move.playerId);
    m_cardGame.applyMove(move);
    m_GUI->revealCard(move, m_cardGame.m_playerHands[move.playerId][move.cardIndex]);
    m_GUI->updateDefusingNumber(m_cardGame.m_defusedCard);

    // wait and start new game
    if(m_cardGame.m_isGameFinished) {
        addWinnerScore();
        updateScore();
        showWinners();
        QTimer::singleShot(5000,this,[this](){initGame();});
        return;
    }

    m_GUI->yourTurn->setVisible(false);
    if(m_id == m_cardGame.m_wireCutterId) {
        m_GUI->yourTurn->setVisible(true);
    }

    bool isEndOfRound = m_cardGame.m_cardPlayedCount == 0;
    if(isEndOfRound) {
        QTimer::singleShot(3000,this,[this](){
            m_GUI->showNextRound(m_cardGame.m_roundNumber);
            showNextRound();
            m_GUI->turnNumber->setText("Turn " + QString::number(m_cardGame.m_cardPlayedCount+1) + "/" + QString::number(m_cardGame.m_playerCount));
            m_players[m_cardGame.m_wireCutterId]->chooseMove(m_cardGame);
            m_isGamePaused = false;
        });
    }
    else {
        m_GUI->turnNumber->setText("Turn " + QString::number(m_cardGame.m_cardPlayedCount+1) + "/" + QString::number(m_cardGame.m_playerCount));
        QCoreApplication::processEvents();
        m_players[m_cardGame.m_wireCutterId]->chooseMove(m_cardGame);
        m_isGamePaused = false;
    }
}

GameManager::~GameManager() {
    if(m_client != nullptr) {
        delete m_client->m_socket;
        delete m_client;
    }
    if(m_players[0] != nullptr) {
        for(int i = 0; i < m_cardGame.m_playerCount ; ++i) {
            delete m_players[i];
        }
    }
}
