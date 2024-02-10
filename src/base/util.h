#ifndef MAZECAVEGENERATOR_SRC_BASE_UTIL_H_
#define MAZECAVEGENERATOR_SRC_BASE_UTIL_H_

#include "base/types.h"
#include "base/constants.h"

#include <random>

namespace mcg::util {

inline int GenRandomNum(int left, int right) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> distribution(left, right);
  return distribution(rng);
}

template <typename Tp>
inline ScaledSize GetScaledCell(const Matrix<Tp> &m) {
  return {float(constants::kSize) / m.GetRows(), float(constants::kSize) / m.GetCols()};
}

}  // namespace mcg::util

#endif  // MAZECAVEGENERATOR_SRC_BASE_UTIL_H_