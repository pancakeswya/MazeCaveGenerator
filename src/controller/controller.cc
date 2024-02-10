#include "controller/controller.h"
#include "model/model.h"

namespace mcg {

Controller::Controller(Model* model) : model_(model) {}

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