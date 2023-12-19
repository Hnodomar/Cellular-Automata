#pragma once

#include <SFML/Graphics.hpp>

enum class terrain_t
{
  LAND,
  WATER,
  MOUNTAIN,
  SAND,
  RED
};

struct colour_t
{
  operator sf::Color() const
  {
    return sf::Color(r, g, b);
  }

  int r, g, b;
};

sf::Color to_color_t(const terrain_t t);

template<terrain_t terrain>
struct terrain_traits_t;

template<>
struct terrain_traits_t<
  terrain_t::LAND
>
{
  static constexpr colour_t COLOUR = {0, 128, 21}; // green
};

template<>
struct terrain_traits_t<
  terrain_t::WATER
>
{
  static constexpr colour_t COLOUR = {0, 77, 230}; // blue
};

template<>
struct terrain_traits_t<
  terrain_t::MOUNTAIN
>
{
  static constexpr colour_t COLOUR = {84, 84, 84}; // grey
};

template<>
struct terrain_traits_t<
  terrain_t::SAND
>
{
  static constexpr colour_t COLOUR = {194, 178, 128};
};

template<terrain_t terrain>
using tc_t = terrain_traits_t<terrain>;
