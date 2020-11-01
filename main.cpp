#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

constexpr int WIDTH = 800, HEIGHT = 600;

namespace {
    int getIndex(int x, int y) {
        return y * WIDTH + x;
    }
}

class Application {
    public:
        Application();
        void run();
    
    private:
        void pollEvents();
        void setCell(int x, int y, sf::Uint8 colour);
        sf::RenderWindow m_window;
        std::vector<sf::Vertex> m_pixels;
};

Application::Application()
    : m_window ({WIDTH, HEIGHT}, "Predator and Prey")
    , m_pixels (WIDTH * HEIGHT) {
        m_window.setFramerateLimit(60);
        for (int x = 0; x < WIDTH; ++x)
            for (int y = 0; y < HEIGHT; ++y) {
                auto index = getIndex(x, y);
                m_pixels[index].position = {x, y};
                setCell(x, y, rand() % 255);
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

void Application::setCell(int x, int y, sf::Uint8 colour) {
    auto index = getIndex(x, y);
    m_pixels[index].color = {colour, colour, colour};
}

int getRandomInt() {
    return std::rand() + 100;
}


int main(int argc, char** argv) {
    Application app;
    app.run();
    return 0;
} 