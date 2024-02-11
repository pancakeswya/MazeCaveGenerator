#ifndef MAZECAVEGENERATOR_SRC_MODEL_MAZE_SOLVER_H_
#define MAZECAVEGENERATOR_SRC_MODEL_MAZE_SOLVER_H_

#include "base/types.h"

namespace mcg::maze {

extern std::pair<bool, SolutionMap> Solve(const WallsMap& maze_map,
                                          const Indices& curr,
                                          const Indices& target);

}  // namespace mcg::maze

#endif  // MAZECAVEGENERATOR_SRC_MODEL_MAZE_SOLVER_H_