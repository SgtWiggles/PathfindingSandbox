#include <SFML\System.hpp>
#include <iostream>

#include "DiffusionMap.h"
#include "Map.h"
#include "MapRenderer.h"
#include "Scenario.h"

#define RENDER

int main() {
  auto [map, scen] = loadMapAndScenario("maps/dragon_age/arena2.map");
  map.print();
  scen.print();
  auto diffusion = DiffusionMap(map);

  sf::RenderWindow window(sf::VideoMode(1920, 1000), "Tile Test");
#ifdef RENDER
  auto renderer = MapRenderer();
#endif RENDER

  // window.setFramerateLimit(60);
  size_t frames = 0;
  sf::Clock clock;
  int sub = 0;
  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e))
      switch (e.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::Resized:
        window.setView(sf::View{{{0.f, 0.f}, sf::Vector2f{window.getSize()}}});
        break;
      }

    for (int b = 0; b < std::max(scen.getTotalBuckets() - sub, 0); ++b)
      for (auto &i : scen.getBucket(b))
        diffusion.setDiffusionValue(map.toIdx(i.gx, i.gy), 1000.f, map);

    diffusion.update(map);
    ++frames;
#ifdef RENDER
    if (frames % 60 == 0) {
      window.clear();
      renderer.render(map, window);
      renderer.render(map, diffusion, window);
      window.display();
    }
#endif RENDER
  }

  std::cout << "fps: " << (float)frames / clock.getElapsedTime().asSeconds();
  std::cin.get();

  return 0;
}
