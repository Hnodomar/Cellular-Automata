#include "util.hpp"

int coord_2d_to_1d(int x, int y)
{
  return y * WIDTH + x;
}
