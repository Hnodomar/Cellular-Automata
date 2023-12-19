#include "terrain.hpp"

sf::Color to_color_t(const terrain_t t)
{
  switch(t) {
    case terrain_t::LAND: {
      return {0, 128, 21};
    }
    case terrain_t::WATER: {
      return {0, 77, 230};
    }
    case terrain_t::MOUNTAIN: {
      return {84, 84, 84};
    }
    case terrain_t::SAND: {
      return {194, 178, 128};
    }
    case terrain_t::RED: {
      return {255, 0, 0};
    }
    default: 
      return {};
  }
}