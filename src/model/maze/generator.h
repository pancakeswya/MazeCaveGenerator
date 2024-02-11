#ifndef MAZECAVEGENERATOR_SRC_MODEL_MAZE_GENERATOR_H_
#define MAZECAVEGENERATOR_SRC_MODEL_MAZE_GENERATOR_H_

#include "base/types.h"

namespace mcg::maze {

extern WallsMap Generate(size_t rows, size_t cols);

}  // namespace mcg::maze

#endif  // MAZECAVEGENERATOR_SRC_MODEL_MAZE_GENERATOR_H_