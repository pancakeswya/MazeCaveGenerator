#ifndef MAZECAVEGENERATOR_MCG_LIB_CAVE_CAVE_H_
#define MAZECAVEGENERATOR_MCG_LIB_CAVE_CAVE_H_

#include "base/defs.h"
#include "lib/matrix/matrix.h"

namespace mcg {

class Cave : public Matrix<int> {
 public:
  void NextGeneration() noexcept;
  void Generate(size_t rows, size_t cols, size_t life_chance, const Range& live,
                const Range& born);

 private:
  size_t life_chance_{};
  Range live_limit_, born_limit_;
  void Generate_();
  void SetFirstGeneration(size_t live_chance);
  size_t CountNeighbours(size_t row, size_t col);
  size_t CheckNeighbour(size_t row, size_t col) noexcept;
};

inline void Cave::NextGeneration() noexcept {
  if (!GetCols() || !GetRows()) {
    return;
  }
  Generate_();
}

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_LIB_CAVE_CAVE_H_
