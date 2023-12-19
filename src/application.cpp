#include "application.hpp"

#include <iostream>

application_t::application_t()
  : m_window ({WIDTH, HEIGHT}, "simulation")
  , _vertices(WIDTH * HEIGHT)
{
  m_window.setFramerateLimit(60);

  _elements.reserve(WIDTH);

  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 0; y < HEIGHT; ++y) {

      const int oned_coord = coord_2d_to_1d(x, y);

      if (_elements.size() <= x) {
        _elements.push_back(std::vector<element_t>());
      }

      const int idx = y * WIDTH + x;

      const double dx = ((double)x / (double)WIDTH) * 1;
      const double dy = ((double)y / (double)HEIGHT) * 1;
          
      auto rng = perlin::compute(dx, dy);

      double w = static_cast<double>(terrain_t::WATER);
      double l = static_cast<double>(terrain_t::LAND);

      auto t = w * rng + l * (1 - rng);

      terrain_t initial_terrain;

      if (t > 0.1) {
        if (t > 0.20) {
          initial_terrain = terrain_t::MOUNTAIN;
        }
        else if (t < 0.11) {
          initial_terrain = terrain_t::SAND;
        }
        else {
          initial_terrain = terrain_t::LAND;
        }
      }
      else {
        initial_terrain = terrain_t::WATER;
      }

      _elements[x].emplace_back(x, y, initial_terrain);
    }
  }
}

void application_t::run()
{
  while (m_window.isOpen()) {
    m_window.clear();

    update();

    m_window.draw(_vertices.data(), _vertices.size(), sf::Points);

    m_window.display();

    pollEvents();
  }
}

void application_t::pollEvents()
{
  sf::Event e;

  while(m_window.pollEvent(e)) {

    switch (e.type) {
      case sf::Event::Closed: {
        m_window.close();
        break;
      }
      case sf::Event::MouseButtonPressed: {
        handle_mouse_press(e.mouseButton);
        break;
      }
      default:
        break;
    }
  }
}

void application_t::handle_mouse_press(sf::Event::MouseButtonEvent mb_e)
{
  switch (mb_e.button) {
    case sf::Mouse::Button::Left: {
      terrain_t terrain = _elements[mb_e.x][mb_e.y].terrain();

      if (_selection_coord) {
        auto [x, y] = *_selection_coord;
        _elements[x][y].deselect();
        _selection_coord.reset();
      }

      if (
        terrain == terrain_t::LAND || terrain == terrain_t::SAND
      )
      {        
        _elements[mb_e.x][mb_e.y].select(_elements);
        _selection_coord = {mb_e.x, mb_e.y};
      }

      break;
    }
    case sf::Mouse::Button::Right: {
      if (_selection_coord) {
        auto [x, y] = *_selection_coord;
        _elements[x][y].deselect();
        _selection_coord.reset();
      }
    }
  }
}

void application_t::update()
{
  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 0; y < HEIGHT; ++y) {
      _vertices[coord_2d_to_1d(x, y)] = _elements[x][y].update();
    }
  }
}

bool application_t::is_alive(const int x, const int y)
{
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return false;
  }

  return true;
}

int application_t::distance(const coord_t to, const coord_t from) const
{
  const double diff_x = std::abs(to.x - from.x);
  const double diff_y = std::abs(to.y - from.y);

  return std::sqrt((diff_x * diff_x) + (diff_y * diff_y)) * 10.0;
}

std::vector<int> application_t::find_path(coord_t start, coord_t goal) const
{
  /*
  std::unordered_map<int, int> came_from;

  auto reconstruct = [&]() {
    std::vector<int> path;
    
    auto it = came_from.find(getIndex(goal.x, goal.y));

    while (it != came_from.end()) {
      path.push_back(it->second);

      it = came_from.find(it->second);
    }

    return path;
  };

  auto path_cmp = [](const path_node_t& l, const path_node_t& r) {
    return l.dist_to_goal < r.dist_to_goal;
  };

  using queue_t = std::priority_queue<
    path_node_t, std::vector<path_node_t>, decltype(path_cmp)
  >;
  
  queue_t open_set(path_cmp);

  std::vector<bool> in_open_set(_vertices.size(), false);

  std::vector<int> best_to_start(_vertices.size(), 10000000);

  std::vector<int> dist_to_goal(_vertices.size(), 10000000);
  dist_to_goal[getIndex(start.x, start.y)] = distance(start, goal);

  open_set.push({start, 0});
  in_open_set[getIndex(start.x, start.y)] = true;

  while (!open_set.empty()) {
  
    auto curr = open_set.top();
    open_set.pop();
    in_open_set[getIndex(curr.node.x, curr.node.y)] = false;

    if (curr.node == goal) {
      return reconstruct();
    }

    const int dx[] = {-1, 0, 1};
    const int dy[] = {-1, 0, 1};

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {

        const int x = curr.node.x + dx[i];
        const int y = curr.node.y + dy[j];

        auto c = _world[x][y];

        const bool is_walkable = {
          c == terrain_t::LAND || c == terrain_t::MOUNTAIN
        };

        if (is_walkable) {

          int dist_to_neighbour = distance({x, y}, curr.node);

          int curr_to_start = {
            best_to_start[getIndex(curr.node.x, curr.node.y)] + dist_to_neighbour
          };

          if (curr_to_start < best_to_start[getIndex(x, y)]) {
            came_from[getIndex(x, y)] = getIndex(curr.node.x, curr.node.y);

            best_to_start[getIndex(x, y)] = curr_to_start;
            dist_to_goal[getIndex(x, y)] = curr_to_start + distance(goal, {x, y});

            if (!in_open_set[getIndex(x, y)]) {
              open_set.push({{x, y}, curr_to_start + distance(goal, {x, y})});
            }
          }
        }
      }
    }
    
  } */ 

  return {};
}
