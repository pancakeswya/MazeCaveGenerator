#ifndef MAZECAVEGENERATOR_MCG_BASE_UTIL_H_
#define MAZECAVEGENERATOR_MCG_BASE_UTIL_H_

#include <random>
#include <fstream>
#include "base/defs.h"
#include "base/settings.h"
#include "lib/matrix/matrix.h"

namespace mcg::util {

inline int GenRandCond(int left, int right) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> distribution(left, right);
  return distribution(rng);
}

template <typename Tp>
inline ScaledSize GetScaledCell(const Matrix<Tp> &m) {
  return {float(settings::kSize) / m.GetRows(), float(settings::kSize) / m.GetCols()};
}

}  // namespace mcg::util

#endif  // MAZECAVEGENERATOR_MCG_BASE_UTIL_H_
