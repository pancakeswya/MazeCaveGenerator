#ifndef MAZECAVEGENERATOR_SRC_BASE_TYPES_H_
#define MAZECAVEGENERATOR_SRC_BASE_TYPES_H_

#include <utility>

#include "base/matrix.h"

namespace mcg {

using Indices = std::pair<int, int>;
using Range = std::pair<int, int>;
using ScaledSize = std::pair<int, int>;

namespace maze {

enum class Vector : short int { kIdle = 0, kUp, kDown, kRight, kLeft };

struct Walls {
  bool right_wall;
  bool bottom_wall;
};

struct Path {
  bool visited;
  Vector vector;
};

using WallsMap = Matrix<Walls>;
using SolutionMap = Matrix<Path>;

}  // namespace maze

namespace cave {

struct Params {
  size_t rows;
  size_t cols;
  size_t life_chance;
  Range live_limit;
  Range born_limit;
};

// using char because bool vector is fucked up
using Walls = int;

using WallsMap = Matrix<Walls>;

}  // namespace cave

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_BASE_TYPES_H_
