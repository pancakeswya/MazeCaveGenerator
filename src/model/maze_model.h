#ifndef MAZECAVEGENERATOR_SRC_MODEL_MAZE_MODEL_H_
#define MAZECAVEGENERATOR_SRC_MODEL_MAZE_MODEL_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg {

class MazeModel {
 public:
  bool Load(const std::string& path);
  bool Save(const std::string& path);

  void Generate(size_t rows, size_t cols);
  bool Solve(const Indices& curr, const Indices& target);

  [[nodiscard]] const maze::WallsMap& GetMap() const noexcept;
  [[nodiscard]] const maze::SolutionMap& GetSolution() const noexcept;

 private:
  maze::WallsMap maze_map_;
  maze::SolutionMap maze_solution_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_MODEL_MAZE_MODEL_H_