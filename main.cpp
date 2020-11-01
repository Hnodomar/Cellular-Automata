#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>


constexpr int WIDTH = 800, HEIGHT = 600;

namespace {
    int getIndex(int x, int y) {
        return y * WIDTH + x;
    }
}

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

Creature::Creature() {
    auto n = rand() % 1000;
    if (n > 100)
        m_type = CreatureType::Nothing;
    else if (n > 50)
        m_type = CreatureType::Prey;
    else
        m_type = CreatureType::Predator;
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

Application::Application()
    : m_window ({WIDTH, HEIGHT}, "Predator and Prey")
    , m_pixels (WIDTH * HEIGHT)
    , m_creatures (WIDTH * HEIGHT) {
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
        return;
    }
    auto nextCreatureType = nextCreature.getType();
    switch (nextCreatureType) {
        case CreatureType::Prey:
            nextCreature.setType(CreatureType::Predator);
            currentCreature.heal(nextCreature.getHealth());
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
            }
            else {
                currentCreature.move(nextCreature);
            }
            break;
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    Application app;
    app.run();
    return 0;
} 