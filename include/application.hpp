#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "creature.hpp"

class Application {
    public:
        Application();
        void run();
        void update();
        
    private:
        void pollEvents();
        void updatePredator(Creature& currentCreature, Creature& nextCreature);
        void updatePrey(Creature& currentCreature, Creature& nextCreature);
        sf::RenderWindow m_window;
        std::vector<sf::Vertex> m_pixels;
        std::vector<Creature> m_creatures;
};

#endif