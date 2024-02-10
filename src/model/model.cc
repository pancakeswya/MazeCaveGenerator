#include "model/model.h"
#include "model/maze/generator.h"
#include "model/cave/generator.h"
#include "model/maze/solver.h"
#include "model/serializer.h"

namespace mcg {

bool Model::LoadMaze(const std::string& path) {
  maze_map_ = maze::
}

bool Model::SaveMaze(const std::string& path) {

}

bool Model::LoadCave(const std::string& path) {

}

bool Model::SaveCave(const std::string& path) {

}

void Model::GenerateMaze(size_t rows, size_t cols) {
  maze_map_ = maze::Generate(rows, cols);
}

void Model::GenerateCave(const cave::Params& params) {
  cave_map_ = cave::Generate(params);
}

void Model::GenerateNextCave(const cave::Params& params) {
  cave_map_ = cave::GenerateNext(cave_map_, params);
}

void Model::SolveMaze(const Indices& curr, const Indices& target) {
  maze_solution_ = maze::Solve(maze_map_, curr, target);
}

const maze::WallsMap& Model::GetMaze() const noexcept {
  return maze_map_;
}

const cave::WallsMap& Model::GetCave() const noexcept {
  return cave_map_;
}

const std::pair<bool, maze::SolutionMap>& Model::GetMazeSolution() const noexcept {
  return maze_solution_;
}

} // namespace mcg