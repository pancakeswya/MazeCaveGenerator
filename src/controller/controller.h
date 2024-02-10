#ifndef MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_
#define MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_

#include "base/types.h"

namespace mcg {

class Model;

class Controller {
  Controller(Model* model);

  const maze::WallsMap& GenerateMaze(size_t rows, size_t cols);
  const cave::WallsMap& GenerateCave(const cave::Params& params);
  const cave::WallsMap& GenerateNextCave(const cave::Params& params);
  const std::pair<bool, maze::SolutionMap>& SolveMaze(const Indices& curr, const Indices& target);

 private:
  Model* model_;
};

} // namespace mcg

#endif // MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_