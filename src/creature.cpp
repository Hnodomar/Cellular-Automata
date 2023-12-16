#include "creature.hpp"

Creature::Creature() {
  auto n = rand() % 1000;

  if (n > 30)
    m_type = CreatureType::Nothing;
  else {
    m_type = CreatureType::Prey;
  }
}  

void Creature::reproduce(Creature& otherCreature) {
    otherCreature.m_health = 10;
    otherCreature.m_type = CreatureType::Prey;
}

void Creature::setHealth(int newHealth) {
    m_health = newHealth;
    return;
}

void Creature::move(Creature& otherCreature) {
    otherCreature.m_health = m_health;
    otherCreature.m_type = m_type;
    m_type = CreatureType::Nothing;
    return;
}

void Creature::update() {
    switch (m_type) {
        case CreatureType::Predator:
            heal(-1);
            break;
        case CreatureType::Prey:
            heal(1);
            break;
        default:
            break;
    }
}

CreatureType Creature::getType() {
    return m_type;
}

int Creature::getHealth() {
    return m_health;
}

void Creature::heal(int amount) {
    m_health += amount;
    if (m_health > MAX_HEALTH) m_health = MAX_HEALTH;
    return;
}

void Creature::setType(CreatureType newType) {
    m_type = newType;
    return;
}

sf::Color Creature::getColour() {
    if (m_type == CreatureType::Nothing)
        return sf::Color::Black;
    else {
        float normalisedHealth = MAX_HEALTH / m_health;
        uint8_t col = normalisedHealth * 255; //to get correct shade of red / green
        switch (m_type) {
            case CreatureType::Predator:
                return {col, 0, 0};
                break;
            case CreatureType::Prey:
                return {0, col, 0};
                break;
            default:
                return sf::Color::Black;
                break;
        }
    }
}
