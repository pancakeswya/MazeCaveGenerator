#ifndef MAZECAVEGENERATOR_SRC_MODEL_MODEL_H_
#define MAZECAVEGENERATOR_SRC_MODEL_MODEL_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg {

class Model {
 public:
  bool LoadMaze(const std::string& path);
  bool LoadCave(const std::string& path);

  bool SaveMaze(const std::string& path);
  bool SaveCave(const std::string& path);

  void GenerateMaze(size_t rows, size_t cols);
  void GenerateCave(const cave::Params& params);
  void GenerateNextCave(const cave::Params& params);
  void SolveMaze(const Indices& curr, const Indices& target);

  [[nodiscard]] const maze::WallsMap& GetMaze() const noexcept;
  [[nodiscard]] const cave::WallsMap& GetCave() const noexcept;
  [[nodiscard]] const std::pair<bool, maze::SolutionMap>& GetMazeSolution()
      const noexcept;

 private:
  cave::WallsMap cave_map_;
  maze::WallsMap maze_map_;
  std::pair<bool, maze::SolutionMap> maze_solution_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_MODEL_MODEL_H_