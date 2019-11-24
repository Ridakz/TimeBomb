#ifndef CARD_H
#define CARD_H

class Card {

public :

    enum CardValue {
        Neutral,
        Bomb,
        Defusing
    };

    Card() = default;
    Card(CardValue v);
    Card(const Card& card);
    bool operator==(const Card& c);
    Card& operator=(const Card& c);

    CardValue m_value;
    bool m_isRevealed;

    ~Card() = default;


};



#endif // CARD_H
