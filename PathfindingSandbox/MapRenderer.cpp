#include "MapRenderer.h"

#include <array>
#include <math.h>

MapRenderer::MapRenderer() : m_renderRect() {}

void MapRenderer::render(const Map &map, sf::RenderWindow &window) {
  static const std::array<sf::Color, (size_t)TileType::TOTAL> fillColors = {
      sf::Color{255, 255, 255, 255}, sf::Color{0, 0, 0, 255},
      sf::Color{132, 46, 0, 255}, sf::Color{0, 68, 132, 255},
      sf::Color{220, 66, 244, 255}};

  auto [mw, mh] = map.getSize();
  auto ws = window.getSize();
  float tw = (float)ws.x / (float)mw;
  float th = (float)ws.y / (float)mh;
  m_renderRect.setSize(sf::Vector2f(tw, th));

  const auto &tiles = map.getTileData();
  for (int i = 0, end = tiles.size(); i < end; ++i) {
    const auto &tile = tiles[i];
    m_renderRect.setFillColor(fillColors[(int)tile]);
    auto [x, y] = map.toLocation(i);
    m_renderRect.setPosition(x * tw, y * th);
    window.draw(m_renderRect);
  }
}

namespace {
sf::Color heatColor(float min, float max, float val) {
  float ratio = 2 * (val - min) / (max - min);
  float b = std::max(0, (int)(255 * (1 - ratio)));
  float r = std::max(0, (int)(255 * (ratio - 1)));
  float g = 255 - b - r;
  float a = 255.f * ratio * 0.5f;
  return sf::Color(r, g, b, a);
}
} // namespace

void MapRenderer::render(const Map &map, const DiffusionMap &diff,
                         sf::RenderWindow &window) {

  auto [mw, mh] = map.getSize();
  auto ws = window.getSize();
  float tw = (float)ws.x / (float)mw;
  float th = (float)ws.y / (float)mh;
  m_renderRect.setSize(sf::Vector2f(tw, th));

  const auto &tiles = map.getTileData();
  const auto &diffs = diff.getMap();
  const auto &maxDiff = std::log10f(diff.maxDiffusion);

  for (int i = 0, end = tiles.size(); i < end; ++i) {
    const auto &tile = tiles[i];

    m_renderRect.setFillColor(heatColor(0, maxDiff, std::log10f(diffs[i])));
    auto [x, y] = map.toLocation(i);
    m_renderRect.setPosition(x * tw, y * th);
    window.draw(m_renderRect);
  }
}
