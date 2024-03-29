#include "model/maze_model.h"

#include "model/maze/generator.h"
#include "model/maze/serializer.h"
#include "model/maze/solver.h"

namespace mcg {

bool MazeModel::Load(const std::string& path) {
  auto [ok, maze_map] = maze::Unmarshal(path);
  maze_map_ = std::move(maze_map);
  return ok;
}

bool MazeModel::Save(const std::string& path) {
  return maze::Marshal(maze_map_, path);
}

void MazeModel::Generate(size_t rows, size_t cols) {
  maze_solution_ = {};
  maze_map_ = maze::Generate(rows, cols);
}

bool MazeModel::Solve(const Indices& curr, const Indices& target) {
  auto [solved, solution] = maze::Solve(maze_map_, curr, target);
  maze_solution_ = solution;
  return solved;
}

const maze::WallsMap& MazeModel::GetMap() const noexcept { return maze_map_; }

const maze::SolutionMap& MazeModel::GetSolution() const noexcept {
  return maze_solution_;
}

}  // namespace mcg