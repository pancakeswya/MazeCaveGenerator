#ifndef MAZECAVEGENERATOR_SRC_BASE_UTIL_H_
#define MAZECAVEGENERATOR_SRC_BASE_UTIL_H_

#include <fstream>
#include <random>

#include "base/constants.h"
#include "base/types.h"

namespace mcg::util {

inline int GenRandomNum(int left, int right) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> distribution(left, right);
  return distribution(rng);
}

template <typename Tp>
inline ScaledSize GetScaledCell(int w, int h, const Matrix<Tp>& m) {
  return {float(w) / m.GetRows(), float(h) / m.GetCols()};
}

template <typename Tp, typename Pred>
void SaveWalls(const Matrix<Tp>& mcg, Pred GetWalls, std::ofstream& os) {
  for (size_t i = 0; i < mcg.GetRows(); ++i) {
    for (size_t j = 0; j < mcg.GetCols(); ++j) {
      os << GetWalls(mcg[i][j]);
      if (j != mcg.GetCols() - 1) {
        os << ' ';
      }
    }
    os << '\n';
  }
}

}  // namespace mcg::util

#endif  // MAZECAVEGENERATOR_SRC_BASE_UTIL_H_
