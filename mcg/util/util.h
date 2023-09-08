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

template <typename Tp, typename Pred>
void SaveCells(Matrix<Tp> &mcg, Pred GetCell, std::ofstream &os) {
  for (size_t i = 0; i < mcg.GetRows(); ++i) {
    for (size_t j = 0; j < mcg.GetCols(); ++j) {
      os << GetCell(mcg[i][j]);
      if (j != mcg.GetCols() - 1) {
        os << ' ';
      }
    }
    os << '\n';
  }
}

}  // namespace mcg::util

#endif  // MAZECAVEGENERATOR_MCG_BASE_UTIL_H_
