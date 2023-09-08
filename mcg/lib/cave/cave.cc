#include "cave.h"

#include "util/util.h"
#include <iostream>

namespace mcg {

inline size_t Cave::CheckNeighbour(size_t row, size_t col) noexcept {
  if (row >= GetRows() || col >= GetCols()) {
    return true;
  }
  return (*this)[row][col] != 0;
}

inline size_t Cave::CountNeighbours(size_t row, size_t col) {
  return CheckNeighbour(row, col - 1) + CheckNeighbour(row, col + 1) +
         CheckNeighbour(row - 1, col) + CheckNeighbour(row + 1, col) +
         CheckNeighbour(row - 1, col - 1) + CheckNeighbour(row - 1, col + 1) +
         CheckNeighbour(row + 1, col - 1) + CheckNeighbour(row + 1, col + 1);
}

void Cave::SetFirstGeneration(size_t live_chance) {
  for (auto& cell : *this) {
    int chance = util::GenRandCond(0, 100);
    if (chance <= live_chance) {
      cell = 1;
    }
  }
}

void Cave::Generate(size_t rows, size_t cols, size_t life_chance,
                    const Range& live, const Range& born) {
  if (rows == 0 || cols == 0) {
    return;
  }
  Clear();
  SetRows(rows);
  SetCols(cols);
  if (life_chance == 0) {
    return;
  }
  life_chance_ = life_chance;
  live_limit_ = live;
  born_limit_ = born;
  SetFirstGeneration(life_chance_);
  Generate_();
}

void Cave::Generate_() {
  Matrix<int> tmp = static_cast<Matrix<int>&>(*this);
  for (size_t row = 0; row != GetRows(); ++row) {
    for (size_t col = 0; col != GetCols(); ++col) {
      size_t count = CountNeighbours(row, col);
      if (At(row, col) == 1 &&
          (count < live_limit_.first || count > live_limit_.second)) {
        tmp[row][col] = 0;
      } else if (At(row, col) == 0 && count >= born_limit_.first &&
                 count <= born_limit_.second) {
        tmp[row][col] = 1;
      }
    }
  }
  std::copy(tmp.begin(), tmp.end(), begin());
}

}  // namespace mcg
