#include "entity.hpp"

entity_t::entity_t(
  const entity_name_t      e,
  std::function<void(int)> on_pos_change
)
  : _entity(e)
  , _on_pos_change(on_pos_change)
{

}

void entity_t::update()
{
  if (!_path.empty()) {
    set_position(_path.back());
    _path.pop_back();
  }
}

void entity_t::set_path(std::vector<int> path)
{
  _path = path;
}

void entity_t::set_position(const int pos)
{
  _on_pos_change(pos);
}
