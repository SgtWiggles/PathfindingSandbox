#include "CostMap.h"

#include <array>

CostMap::CostMap(const Map &map) : m_map(), m_size(map.getSize()) {
  static const std::array<uint8_t, (size_t)TileType::TOTAL> tileCosts = {
      1, 0, 0, 0, 0};

  auto [ww, wh] = map.getSize();
  m_map.resize(ww * wh);

  const auto &tiles = map.getTileData();
  for (int i = 0, end = m_map.size(); i < end; ++i) {
    m_map[i] = tileCosts[(int)tiles[i]];
  }
}
