#ifndef CREATURE_H
#define CREATURE_h

#include <random>
#include <SFML/Graphics.hpp>

enum class CreatureType {
    Predator = 0,
    Prey = 1,
    Nothing = 2
};

class Creature {
    public:
        constexpr static int MAX_HEALTH = 100;
        Creature();

        sf::Color getColour();

        void setType(CreatureType newType);
        CreatureType getType();
        void setHealth(int newHealth);
        int getHealth();

        void heal (int amount);
        void update();
        void move(Creature& otherCreature);
        void reproduce(Creature& otherCreature);
    private:
        CreatureType m_type;
        int m_health = MAX_HEALTH / 5;
};

#endif