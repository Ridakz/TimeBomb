#include "Model/card.h"

Card::Card(Card::CardValue v) : m_value(v), m_isRevealed(false) {}

Card::Card(const Card &card) : m_value(card.m_value), m_isRevealed(false) {}

bool Card::operator==(const Card &c) {
    return m_value == c.m_value;
}

Card &Card::operator=(const Card &c) {
    m_value = c.m_value;
    m_isRevealed = c.m_isRevealed;
    return *this;
}
