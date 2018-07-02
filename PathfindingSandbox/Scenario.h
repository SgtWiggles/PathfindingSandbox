#pragma once
#include <string_view>
#include <vector>

#include "Map.h"

struct ScenarioCase {
  int bucket;
  int sx, sy;
  int gx, gy;
  float optimal;
};

class Scenario {
public:
  void loadScenario(const std::string_view path);

  const std::vector<ScenarioCase> &getBucket(int bucket) const;
  int getTotalBuckets() const;
  void addCase(ScenarioCase cas);
  void print() const;

private:
  std::vector<std::vector<ScenarioCase>> m_buckets;
};

std::tuple<Map, Scenario> loadMapAndScenario(std::string mapPath);
