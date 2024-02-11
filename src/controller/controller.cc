#include "controller/controller.h"

#include "model/cave_model.h"
#include "model/maze_model.h"

namespace mcg {

Controller::Controller(MazeModel* maze_model, CaveModel* cave_model) noexcept
    : maze_model_(maze_model), cave_model_(cave_model) {}

std::pair<bool, const maze::WallsMap&> Controller::LoadMaze(
    const std::string& path) {
  bool ok = maze_model_->Load(path);
  return {ok, maze_model_->Get()};
}

std::pair<bool, const cave::WallsMap&> Controller::LoadCave(
    const std::string& path) {
  bool ok = cave_model_->Load(path);
  return {ok, cave_model_->Get()};
}

bool Controller::SaveMaze(const std::string& path) {
  return maze_model_->Save(path);
}

bool Controller::SaveCave(const std::string& path) {
  return cave_model_->Save(path);
}

const maze::WallsMap& Controller::GenerateMaze(size_t rows, size_t cols) {
  maze_model_->Generate(rows, cols);
  return maze_model_->Get();
}

const cave::WallsMap& Controller::GenerateCave(const cave::Params& params) {
  cave_model_->Generate(params);
  return cave_model_->Get();
}

const cave::WallsMap& Controller::GenerateNextCave(const cave::Params& params) {
  cave_model_->GenerateNext(params);
  return cave_model_->Get();
}

const std::pair<bool, maze::SolutionMap>& Controller::SolveMaze(
    const Indices& curr, const Indices& target) {
  maze_model_->Solve(curr, target);
  return maze_model_->GetSolution();
}

}  // namespace mcg