#include "DiffusionMap.h"

#include <array>

DiffusionMap::DiffusionMap(const Map &map) : m_diffusion(), m_diff2() {
  auto [mw, mh] = map.getSize();
  m_diffusion.resize(mw * mh);
  m_diff2.resize(mw * mh);
  maxDiffusion = 0.f;
}

namespace {
template <class T> T sign(T val) {
  if (val != 0)
    return (T)1;
  return (T)0;
}
} // namespace

void DiffusionMap::update(const Map &map) {
  static const std::array<float, (size_t)TileType::TOTAL> tileDiffuseValues = {
      0.25f, 0.0f, 0.0f, 0.f, 0.f};
  static constexpr float DIFF_FACTOR = 0.125;
  static constexpr float DECAY_FACTOR = 0.95f;

  auto diffuse_tile = [this, &map](int x, int y) {
    const auto v = map.isInbounds(x, y);
    if (v == Map::INVALID_TILE)
      return 0.f;
    return m_diffusion[v];
  };

  for (int i = 0, end = m_diffusion.size(); i < end; ++i) {
    auto [x, y] = map.toLocation(i);
    m_diff2[i] =
        map.getTile(i) == TileType::PASSABLE
            ? DECAY_FACTOR * m_diffusion[i] +
                  DIFF_FACTOR * ((diffuse_tile(x - 1, y) - 2 * m_diffusion[i] +
                                  diffuse_tile(x + 1, y)) +
                                 (diffuse_tile(x, y - 1) - 2 * m_diffusion[i] +
                                  diffuse_tile(x, y + 1)))
            : 0;
    maxDiffusion = std::max(maxDiffusion, m_diff2[i]);
  }

  std::swap(m_diffusion, m_diff2);
}

void DiffusionMap::setDiffusionValue(int idx, float value, const Map &map) {
  m_diffusion[idx] = value;
}

const std::vector<float> DiffusionMap::getMap() const { return m_diffusion; }
