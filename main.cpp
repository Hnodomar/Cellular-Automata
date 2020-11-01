#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>

constexpr int WIDTH = 800, HEIGHT = 600;
const int MAX_HEALTH = 100;

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
        Creature();
        sf::Color getColour();
        void setType(CreatureType newType);
        void heal (int amount);
        int getHealth();
        void Creature::update();
    private:
        CreatureType m_type;
        int m_health = 100;
};

Creature::Creature() {
    static std::minstd_rand randDevice(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 2);

    m_type = static_cast<CreatureType>(dist(randDevice)); //set m_type to a random number between 1 or 2
}                                                         //cast to get it correct type

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
    
    private:
        void pollEvents();
        void update();
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
            CreatureType currentType = m_creatures[index].m_type;
            if (currentType == CreatureType::Nothing) //Only updating living creatures
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
            CreatureType nextType = m_creatures[nextIndex].m_type();

            currentType.update();
            switch (currentType) {
                case CreatureType::Predator:
                    updatePredator(currentType, nextType);
                    break;
                case CreatureType::Prey:
                    updatePrey(currentType, nextType);
                    break;
                default:
                    break;
            }
            setCellColour(x, y, m_creatures[index].getColour());
        }
}

void Application::setCellColour(int x, int y, sf::Color colour) {

}

void Application::updatePredator() {

}

void Application::updatePrey() {

}

int getRandomInt() {
    return std::rand() + 100;
}


int main(int argc, char** argv) {
    Application app;
    app.run();
    return 0;
} 