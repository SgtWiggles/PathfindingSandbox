#pragma once
#include "Map.h"
#include <vector>

class DiffusionMap {
public:
  DiffusionMap(const Map &map);
  void update(const Map &map);
  void setDiffusionValue(int idx, float value, const Map &map);
  const std::vector<float> getMap() const;

  float maxDiffusion;

private:
  std::vector<float> m_diffusion;
  std::vector<float> m_diff2;
  std::vector<int> m_centers;
};
