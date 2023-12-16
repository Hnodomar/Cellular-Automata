#include "application.hpp"

#include <iostream>

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
{
  m_window.setFramerateLimit(60);

  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 0; y < HEIGHT; ++y) {
      auto index = getIndex(x, y);
      
      m_pixels[index].position = {(float)x, (float)y};
      
      m_pixels[index].color = m_creatures[index].getColour();
    }
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
  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 0; y < HEIGHT; ++y) {
    
      const auto c_idx = getIndex(x, y);

      auto& creature = m_creatures[c_idx];

      int living_n = 0;

      living_n += is_alive(x + 1, y);

      living_n += is_alive(x + 1, y + 1);
      living_n += is_alive(x,     y + 1);
      living_n += is_alive(x - 1, y + 1);

      living_n += is_alive(x - 1, y);

      living_n += is_alive(x - 1, y - 1);
      living_n += is_alive(x,     y - 1);
      living_n += is_alive(x + 1, y - 1);

      switch (creature.getType()) {
        case CreatureType::Nothing: {
          if (living_n == 3) {
            creature.setType(CreatureType::Prey);
          }

          break;
        }
        case CreatureType::Prey: {
          if (living_n < 2 || living_n > 3) {
            creature.setType(CreatureType::Nothing);
          }

          break;
        }
        default: {
          break;
        }
      }

      m_pixels[c_idx].color = creature.getColour();
    }
  }
}

bool Application::is_alive(const int x, const int y)
{
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return false;
  }

  return m_creatures[getIndex(x, y)].getType() == CreatureType::Prey;
}
