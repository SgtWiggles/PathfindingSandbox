#pragma once
#include <vector>

enum class TileType { PASSABLE, OUT_OF_BOUNDS, TREE, SWAMP, WATER, TOTAL };

class Map {
public:
  static constexpr int INVALID_TILE = -1;
  void loadMap(std::string filepath);
  void print() const;

  const std::vector<TileType> &getTileData() const;
  std::tuple<int, int> getSize() const;
  const TileType getTile(int idx) const;

  std::tuple<int, int> toLocation(int idx) const;
  int toIdx(int x, int y) const;
  int isInbounds(int x, int y) const;

private:
  int m_width;
  int m_height;
  std::vector<TileType> m_tiles;
};
