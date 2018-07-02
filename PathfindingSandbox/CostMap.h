#pragma once
#include <vector>

#include "Map.h"

class CostMap {
public:
  CostMap(const Map &map);

private:
  std::vector<uint8_t> m_map;
  std::tuple<int, int> m_size;
};
