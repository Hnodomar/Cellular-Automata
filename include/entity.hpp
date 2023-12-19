#pragma once

#include <vector>
#include <functional>

enum class entity_name_t
{
  NONE,
  TREE,
  GREEN,
  RED
};

class entity_t
{
public:

  entity_t(const entity_name_t e, std::function<void(int)> on_pos_change);

  void update();

  void set_path(std::vector<int> path);

  void set_position(const int pos);

private:

  std::vector<int> _path;

  const entity_name_t _entity;

  std::function<void(int)> _on_pos_change;
};
