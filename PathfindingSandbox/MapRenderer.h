#pragma once
#include <SFML\Graphics.hpp>

#include "DiffusionMap.h"
#include "Map.h"

class MapRenderer {
public:
  MapRenderer();
  void render(const Map &map, sf::RenderWindow &window);
  void render(const Map &map, const DiffusionMap &diff,
              sf::RenderWindow &window);

private:
  sf::RectangleShape m_renderRect;
};
