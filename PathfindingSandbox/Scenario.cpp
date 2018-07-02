#include "Scenario.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Scenario::loadScenario(const std::string_view path) {
  auto file = std::fstream(path.data());
  std::string line;
  std::string map;
  int w, h;

  std::getline(file, line);
  while (std::getline(file, line)) {
    ScenarioCase c;

    auto iss = std::istringstream(line);
    if (!(iss >> c.bucket >> map >> w >> h >> c.sx >> c.sy >> c.gx >> c.gy >>
          c.optimal)) {
      // TODO complain
      break;
    }

    addCase(c);
  }
}

const std::vector<ScenarioCase> &Scenario::getBucket(int bucket) const {
  return m_buckets[bucket];
}

int Scenario::getTotalBuckets() const { return m_buckets.size(); }

void Scenario::addCase(ScenarioCase cas) {
  if (m_buckets.size() <= cas.bucket)
    m_buckets.resize(cas.bucket + 1);
  m_buckets[cas.bucket].push_back(cas);
}

#define COUT_PAIR(LEFT, RIGHT) "(" << LEFT << "," << RIGHT << ")"

void Scenario::print() const {
  for (int i = 0, end = m_buckets.size(); i < end; ++i) {
    const auto &bucket = m_buckets[i];
    for (int j = 0, end2 = bucket.size(); j < end2; ++j) {
      const auto &cbucket = bucket[j];
      std::cout << i << COUT_PAIR(cbucket.sx, cbucket.sy) << "->"
                << COUT_PAIR(cbucket.gx, cbucket.gy) << "\n";
    }
  }
}

std::tuple<Map, Scenario> loadMapAndScenario(std::string mapPath) {
  Map map;
  map.loadMap(mapPath);
  Scenario scen;
  scen.loadScenario(mapPath + ".scen");
  return std::make_tuple(map, scen);
}
