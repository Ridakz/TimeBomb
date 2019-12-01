#include "Model/cardgame.h"
#include <random>
#include <assert.h>

CardGame::CardGame(int playerCount) : m_playerCount (playerCount) {
    //assert( playerCount >= minPlayers && playerCount <= maxPlayers );
}

void CardGame::startGame() {
    m_isGameFinished = false;
    m_deck.init(m_playerCount);
    m_defusedCard = 0;
    m_wireCutterId = m_matchNumber%m_playerCount;
    ++m_matchNumber;
    m_roundNumber = 1;
    m_cardPlayedCount = 0;
    hideCards();
    setPlayerSides();
    dealCards();
}

void CardGame::hideCards() {
    for(int i = 0; i < m_playerCount ; ++i) {
        for(int j = 0; j < 5; ++j) {
            m_playerHands[i][j].m_isRevealed = false;
        }
    }
}

void CardGame::dealCards() {
    m_deck.shuffle();
    for(int i = 0; i < m_playerCount ; ++i) {
        for(int j = 0; j < 6 - m_roundNumber; ++j) {
           m_playerHands[i][j] = m_deck.cards[i*(6-m_roundNumber) + j] ;
        }
    }
}

void CardGame::setPlayerSides() {
    int index [m_playerCount];
    for(int i = 0; i < m_playerCount ; ++i) {
        index[i] = i;
    }
    int terroristIndex = (rand() % (m_playerCount));
    m_playerSide[terroristIndex] = Terrorist;
    index[terroristIndex] = m_playerCount -1;

    terroristIndex = (rand() % (m_playerCount-1));
    m_playerSide[terroristIndex] = Terrorist;
    index[terroristIndex] = m_playerCount - 2;

    for(int i = 0; i < m_playerCount - 2; ++i) {
        m_playerSide[index[i]] = Sherlock;
    }
}

bool CardGame::isWinner(int playerId) const {
    return m_playerSide[playerId] == m_winner;
}

bool CardGame::canApply(Move move, int playId) const {
    bool isCardRevealed = m_playerHands[move.playerId][move.cardIndex].m_isRevealed;
    bool isOwnCard = playId == move.playerId;
    bool isPlayerTurn = playId == m_wireCutterId;
    return isPlayerTurn &&  !isCardRevealed && !isOwnCard && !m_isGameFinished;
}

void CardGame::cardsCount(int playerId, int cards[]) {
    int neutrals = 0, defusings = 0, bomb = 0;
    for(int i = 0; i < 6-m_roundNumber ; ++i) {
        Card c = m_playerHands[playerId][i];
        if(c.m_value == Card::Neutral) {
            ++neutrals;
        }
        else if(c.m_value == Card::Defusing) {
            ++defusings;
        }
        else {
            ++bomb;
        }
    }
    cards[0] = neutrals;
    cards[1] = defusings;
    cards[2] = bomb;
}

void CardGame::applyMove(Move move) {

    Card& card =  m_playerHands[move.playerId][move.cardIndex];
    card.m_isRevealed = true;
    m_wireCutterId = move.playerId;
    ++m_cardPlayedCount ;
    m_deck.remove(card);

    if(card.m_value == Card::Bomb) {
        m_isGameFinished = true;
        m_winner = Terrorist;
        return;
    }
    else if(card.m_value == Card::Defusing) {
        ++m_defusedCard;
    }

    bool isBombDefused = m_defusedCard == m_playerCount;
    if(isBombDefused) {
        m_isGameFinished = true;
        m_winner = Sherlock;
        return;
    }

    bool isEndOfRound = m_cardPlayedCount == m_playerCount;
    if(isEndOfRound) {
        bool isLastRound = m_roundNumber == 4;
        if(isLastRound) {
            m_isGameFinished = true;
            m_winner = Terrorist;
            return;
        }
        else { // next round
            ++m_roundNumber;
            dealCards();
            m_cardPlayedCount = 0;
        }
    }
}

CardGame::~CardGame() {

}
