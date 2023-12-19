#pragma once

#include "types.hpp"

#include <vector>
#include <array>
#include <iostream>
#include <functional>

template<int RADIUS>
constexpr auto diffs()
{
  constexpr size_t N = (2 * RADIUS) + 1;

  std::array<int, N> diffs;

  for (int i = 0; i < RADIUS; ++i) {
    diffs[i] = (RADIUS - i) * -1;
  }

  diffs[RADIUS] = 0;

  for (int i = N - 1, j = 0; i > RADIUS; --i, ++j) {
    diffs[i] = RADIUS - j;
  }

  return diffs;
}

template<int RADIUS>
void diff_radius_op(std::function<void(int, int)> op)
{
  constexpr auto dxs = diffs<RADIUS>(), 
                 dys = diffs<RADIUS>();

  for (const auto dx : dxs) {
    for (const auto dy : dys) {
      op(dx, dy);
    }
  }
}

template<int RADIUS, typename T>
void grid_square_op(
  std::vector<std::vector<T>>&    grid,
  coord_t                         centre,
  std::function<void(T&)>         op
)
{
  const int dxs[] = {-1, 0, 1};
  const int dys[] = {-1, 0, 1};
  
  auto& e = grid[0][0];

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {

      const int x = centre.x;
      const int y = centre.y;

      const int dx = dxs[i];
      const int dy = dys[j];

      
      /*const bool out_of_bounds = {
        (centre.x + dx < 0) || (centre.x + dx >= grid.size()) ||
        (centre.y + dy < 0) || (centre.y + dy >= grid[0].size())
      };

      if (out_of_bounds) {
        throw std::runtime_error("grid_square_op(): out of bounds");
      }*/

      //op(grid[x][y]);
    }
  }

}

int coord_2d_to_1d(int x, int y);
