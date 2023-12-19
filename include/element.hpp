#pragma once

#include "terrain.hpp"
#include "entity.hpp"
#include "types.hpp"
#include "util.hpp"

#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class element_t;

using elements_t = std::vector<
  std::vector<element_t>
>;

class element_t
{
public:

  element_t(const int x, const int y, const terrain_t t);

  void set_terrain(const terrain_t t);

  terrain_t terrain() const;

  sf::Vertex update();

  void select(elements_t& elements);

  void deselect();

  std::optional<entity_t> entity;

  int get_oned_pos() const;

private:

  class select_state_t
  {
  public:

    select_state_t(
      coord_t     centre,
      elements_t& elements
    );

    ~select_state_t();

  private:

    std::vector<
      std::vector<element_t>
    >&                       _elements;
    coord_t                  _centre;
    

    std::unordered_map<int, terrain_t> _prev_terrains;
  };

  const int _x;
  const int _y;

  terrain_t _terrain;

  std::optional<select_state_t> _select_state;
};
