#include "Model/deck.h"
#include <algorithm>
#include <random>


Deck::Deck()
{

}

void Deck::init (int playerCount) {
    cards.clear();
    for(int i = 0; i < playerCount ; ++i) {
        cards.push_back(Card(Card::Defusing));
    }
    for(int i = 0; i < 15 + (playerCount - 4) * 4 ; ++i) {
        cards.push_back(Card(Card::Neutral));
    }
    cards.push_back(Card(Card::Bomb));
}

void Deck::shuffle() {
    auto rng = std::default_random_engine {static_cast<unsigned int>(rand())};
    std::shuffle(cards.begin(),cards.end(),rng);
}

void Deck::remove(Card c) {
    cards.erase(std::find(cards.begin(),cards.end(),c));
//    for(int i = 0; i < cards.size() ; ++i) {
//        if(c.m_value == cards[i].m_value) {
//            cards.erase(cards.begin() + i);
//            return;
//        }
//    }
}



