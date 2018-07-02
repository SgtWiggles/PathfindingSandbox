#include "Map.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Map::loadMap(std::string filepath) {
  auto file = std::fstream(filepath);
  std::string line;
  std::getline(file, line); // Discard line

  auto lam = [&file, &line]() {
    std::getline(file, line);
    std::string field;
    int value;
    auto iss = std::istringstream(line);
    if (!(iss >> field >> value)) {
      // complain
    }
    return value;
  };

  m_height = lam();
  m_width = lam();
  m_tiles.resize(m_width * m_height);

  std::getline(file, line); // Discard line
  size_t idx = 0;

  while (std::getline(file, line)) {
    for (char c : line) {
      TileType type = [](char ch) {
        switch (ch) {
        case '.':
          return TileType::PASSABLE;
          break;
        case 'G':
          return TileType::PASSABLE;
          break;
        case '@':
          return TileType::OUT_OF_BOUNDS;
          break;
        case 'O':
          return TileType::OUT_OF_BOUNDS;
          break;
        case 'T':
          return TileType::TREE;
          break;
        case 'S':
          return TileType::SWAMP;
          break;
        case 'W':
          return TileType::WATER;
          break;
        default:
          return TileType::TOTAL;
          break;
        }
      }(c);

      if (type != TileType::TOTAL)
        m_tiles[idx++] = type;
    }
  }
}

void Map::print() const {
  for (int i = 0; i < m_tiles.size(); ++i) {
    if (i % m_width == 0)
      std::cout << "\n";
    std::cout << (int)m_tiles[i];
  }
  std::cout << "\n";
}

const std::vector<TileType> &Map::getTileData() const { return m_tiles; }

std::tuple<int, int> Map::getSize() const {
  return std::make_tuple(m_width, m_height);
}

const TileType Map::getTile(int idx) const { return m_tiles[idx]; }

std::tuple<int, int> Map::toLocation(int idx) const {
  return std::make_tuple(idx % m_width, idx / m_width);
}
int Map::toIdx(int x, int y) const { return x + y * m_width; }

int Map::isInbounds(int x, int y) const {
  if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    return toIdx(x, y);
  return INVALID_TILE;
}
