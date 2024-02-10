#include "controller/controller.h"
#include "model/model.h"

namespace mcg {

Controller::Controller(Model* model) noexcept : model_(model) {}

std::pair<bool, const maze::WallsMap&> Controller::LoadMaze(const std::string& path) {
  bool ok = model_->LoadMaze(path);
  return {ok, model_->GetMaze()};
}

std::pair<bool, const cave::WallsMap&> Controller::LoadCave(const std::string& path) {
  bool ok = model_->LoadCave(path);
  return {ok, model_->GetCave()};
}

bool Controller::SaveMaze(const std::string& path) {
  return model_->SaveMaze(path);
}

bool Controller::SaveCave(const std::string& path) {
  return model_->SaveCave(path);
}

const maze::WallsMap& Controller::GenerateMaze(size_t rows, size_t cols) {
  model_->GenerateMaze(rows, cols);
  return model_->GetMaze();
}

const cave::WallsMap& Controller::GenerateCave(const cave::Params& params) {
  model_->GenerateCave(params);
  return model_->GetCave();
}

const cave::WallsMap& Controller::GenerateNextCave(const cave::Params& params) {
  model_->GenerateNextCave(params);
  return model_->GetCave();
}

const std::pair<bool, maze::SolutionMap>& Controller::SolveMaze(const Indices& curr, const Indices& target) {
  model_->SolveMaze(curr, target);
  return model_->GetMazeSolution();
}

} // namespace mcg