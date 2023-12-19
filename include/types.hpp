#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

constexpr int WIDTH = 1500, HEIGHT = 1080;

struct coord_t
{
  bool operator==(const auto& r) const
  {
    return x == r.x && y == r.y;
  }

  int x, y;
};
