#include "element.hpp"

element_t::element_t(
  const int x,
  const int y,
  const terrain_t t
)
  : _x(x)
  , _y(y)
  , _terrain(t)
{

}

void element_t::set_terrain(const terrain_t t)
{
  _terrain = t;
}

terrain_t element_t::terrain() const
{
  return _terrain;
}

int element_t::get_oned_pos() const
{
  return coord_2d_to_1d(_x, _y);
}

sf::Vertex element_t::update()
{
  sf::Vertex vtx;

  vtx.color = to_color_t(_terrain);

  vtx.position = {
    static_cast<float>(_x),
    static_cast<float>(_y)
  };

  return vtx;
}

void element_t::select(elements_t& elements)
{  
  _select_state.emplace(
    coord_t {
      static_cast<int>(_x),
      static_cast<int>(_y)
    },
    elements
  );
}

void element_t::deselect()
{
  _select_state.reset();
}

element_t::select_state_t::select_state_t(
  coord_t     centre,
  elements_t& elements
)
  : _elements(elements)
  , _centre(centre)
{
  diff_radius_op<1>(
    [&](const int x, const int y) {
      const bool out_of_bounds = {
        (_centre.x + x < 0) || (_centre.x + x >= _elements.size()) ||
        (_centre.y + y < 0) || (_centre.y + y >= _elements[x].size())
      };

      if (out_of_bounds) {
        std::cerr << "grid_square_op(): out of bounds" << std::endl;
        // throw std::runtime_error("grid_square_op(): out of bounds");
      }

      element_t& element = elements[_centre.x + x][_centre.y + y];
      const int pos = element.get_oned_pos();

      _prev_terrains[pos] = element.terrain();
      element.set_terrain(terrain_t::RED);
    }
  );
}

element_t::select_state_t::~select_state_t()
{
  diff_radius_op<1>(
    [&](const int x, const int y) {
      element_t& element = _elements[_centre.x + x][_centre.y + y];
      const int pos = element.get_oned_pos();

      element.set_terrain(_prev_terrains.at(pos));
    }
  );
}
