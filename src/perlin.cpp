#include "perlin.hpp"

namespace perlin
{
  struct vec2
  {
    double x, y;
  };

  double interpolate(const double a0, const double a1, const double w)
  {
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
  }

  vec2 random_gradient(const int ix, const int iy)
  {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width

    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;

    double random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    vec2 v;

    v.x = std::cos(random);
    v.y = std::sin(random);

    return v;
  }

  double dot_grid_gradient(const int ix, const int iy, const double x, const double y)
  {
    vec2 grad = random_gradient(ix, iy);

    const double dx = x - static_cast<double>(ix);
    const double dy = y - static_cast<double>(iy);

    return (dx * grad.x + dy * grad.y);
  }

  double compute(const double x, const double y)
  {
    // Determine grid cell coordinates
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dot_grid_gradient(x0, y0, x, y);
    n1 = dot_grid_gradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dot_grid_gradient(x0, y1, x, y);
    n1 = dot_grid_gradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value; // Will return in range -1 to 1. To make it in range 0 to 1, multiply by 0.5 and add 0.5  }
  }
}
