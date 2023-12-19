#ifndef APPLICATION_H
#define APPLICATION_H

#include "entity.hpp"
#include "terrain.hpp"
#include "perlin.hpp"
#include "types.hpp"
#include "element.hpp"

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <optional>
#include <queue>
#include <memory>

struct path_node_t
{
  coord_t node;
  int     dist_to_goal;
};


class application_t
{
public:

  application_t();

  void run();

  void update();
        
private:

  int distance(const coord_t to, const coord_t from) const;
  
  void pollEvents();

  void handle_mouse_press(sf::Event::MouseButtonEvent mb_e);

  bool is_alive(const int x, const int y);

  std::vector<int> find_path(coord_t start, coord_t goal) const;
    
  sf::RenderWindow m_window;
  
  elements_t  _elements;

  std::vector<sf::Vertex> _vertices;

  std::optional<coord_t> _selection_coord;
};

#endif
