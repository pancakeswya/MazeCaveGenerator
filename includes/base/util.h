#ifndef MAZECAVEGENERATOR_INCLUDES_BASE_UTIL_H_
#define MAZECAVEGENERATOR_INCLUDES_BASE_UTIL_H_

#include <random>
#include <fstream>
#include "matrix.h"

namespace mcg {

namespace {

int GenRandCond(int left, int right) {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<int> distribution(left, right);
  return distribution(rng);
}

template<typename Tp, typename func>
void SaveCells(Matrix<Tp> &mcg, func GetCell, std::ofstream &os) {
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

} // namespace

} // namespace mcg

#endif // MAZECAVEGENERATOR_INCLUDES_BASE_UTIL_H_
