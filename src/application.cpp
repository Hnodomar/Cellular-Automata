#include "application.hpp"

constexpr int WIDTH = 800, HEIGHT = 600;

namespace {
    int getIndex(int x, int y) {
        return y * WIDTH + x;
    }
}

Application::Application()
    : m_window ({WIDTH, HEIGHT}, "Predator and Prey")
    , m_pixels (WIDTH * HEIGHT)
    , m_creatures (WIDTH * HEIGHT)
    #ifdef LOGGING
    , logger(m_creatures)
    #endif
    {
        m_window.setFramerateLimit(60);
        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y) {
                auto index = getIndex(x, y);
                m_pixels[index].position = {(float)x, (float)y};
                m_pixels[index].color = m_creatures[index].getColour();
            }
}

void Application::run() {
    while (m_window.isOpen()) {
        m_window.clear();
        update();
        #ifdef LOGGING
        logger.outputPops();
        #endif
        m_window.draw(m_pixels.data(), m_pixels.size(), sf::Points);
        m_window.display();
        pollEvents();
    }
}

void Application::pollEvents() {
    sf::Event e;
    while(m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Application::update() {
    static std::minstd_rand randDevice(std::time(nullptr));
    for (int x = 0; x < WIDTH; ++x) 
        for (int y = 0; y < HEIGHT; ++y) {
            auto index = getIndex(x, y);
            auto& currentCreature = m_creatures[index];
            CreatureType currentCreatureType = currentCreature.getType();
            
            if (currentCreatureType == CreatureType::Nothing) //Only updating living creatures
                continue;

            std::uniform_int_distribution<int> dist(-1, 1);
            int xChange = dist(randDevice);
            int yChange = dist(randDevice);
            
            int xNext = x + xChange;
            int yNext = y + yChange;
            if (xNext < 0 || xNext >= WIDTH) 
                continue; //overflow check
            if (yNext < 0 || yNext >= HEIGHT) 
                continue;

            auto nextIndex = getIndex(xNext, yNext);
            auto& nextCreature = m_creatures[nextIndex];

            

            currentCreature.update();
            switch (currentCreatureType) {
                case CreatureType::Predator:
                    updatePredator(currentCreature, nextCreature);
                    break;
                case CreatureType::Prey:
                    updatePrey(currentCreature, nextCreature);
                    break;
                default:
                    break;
            }
            m_pixels[index].color = m_creatures[index].getColour();
            m_pixels[nextIndex].color = m_creatures[nextIndex].getColour();
        }
}

void Application::updatePredator(Creature& currentCreature, Creature& nextCreature) {
    if (currentCreature.getHealth() <= 0) {
        currentCreature.setType(CreatureType::Nothing);
        #ifdef LOGGING
            --logger.num_pred;
        #endif
        return;
    }
    auto nextCreatureType = nextCreature.getType();
    switch (nextCreatureType) {
        case CreatureType::Prey:
            nextCreature.setType(CreatureType::Predator);
            currentCreature.heal(nextCreature.getHealth());
            #ifdef LOGGING
                ++logger.num_pred;
                --logger.num_prey;
            #endif
            break;
        case CreatureType::Predator:
            break;
        case CreatureType::Nothing:
            currentCreature.move(nextCreature);
            break;
    }
}

void Application::updatePrey(Creature& currentCreature, Creature& nextCreature) {
    bool reproduce = false;
    auto nextCreatureType = nextCreature.getType();
    if (currentCreature.getHealth() >= Creature::MAX_HEALTH) {
        currentCreature.setHealth(10);
        reproduce = true;
    }
    switch (nextCreatureType) {
        case CreatureType::Prey:
            break;
        case CreatureType::Predator:
            break;
        case CreatureType::Nothing:
            if (reproduce) {
                currentCreature.reproduce(nextCreature);
                #ifdef LOGGING
                    ++logger.num_prey;
                #endif
            }
            else {
                currentCreature.move(nextCreature);
            }
            break;
    }
}
