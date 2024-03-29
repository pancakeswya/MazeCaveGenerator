#ifndef MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_
#define MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg {

class MazeModel;
class CaveModel;

class Controller {
 public:
  explicit Controller(MazeModel* maze_model, CaveModel* cave_model) noexcept;

  std::pair<bool, const maze::WallsMap&> LoadMaze(const std::string& path);
  std::pair<bool, const cave::WallsMap&> LoadCave(const std::string& path);

  bool SaveMaze(const std::string& path);
  bool SaveCave(const std::string& path);

  const maze::WallsMap& GenerateMaze(size_t rows, size_t cols);
  const cave::WallsMap& GenerateCave(const cave::Params& params);
  const cave::WallsMap& GenerateNextCave(const cave::Params& params);
  std::pair<bool, const maze::SolutionMap&> SolveMaze(const Indices& curr,
                                                      const Indices& target);

 private:
  MazeModel* maze_model_;
  CaveModel* cave_model_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_CONTROLLER_CONTROLLER_H_