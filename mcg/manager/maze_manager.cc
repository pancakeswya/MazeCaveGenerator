#include "maze_manager.h"
#include "util/util.h"

namespace mcg {

bool MazeManager::Open(std::string_view path) {
  maze_.Clear();
  std::ifstream file(path.data(), std::ifstream::binary);
  if (!file.is_open()) {
    return false;
  }
  size_t rows, cols;
  file >> rows >> cols;
  maze_.SetRows(rows);
  maze_.SetCols(cols);
  for (auto &cell : maze_) {
    file >> cell.right_wall;
  }
  char c;
  do {
    file.get(c);
  } while (file.good() && c != '\n');
  for (auto &cell : maze_) {
    file >> cell.bottom_wall;
  }
  return true;
}

bool MazeManager::Save(std::string_view path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << maze_.GetRows() << ' ' << maze_.GetCols() << ' ' << '\n';
  util::SaveCells(
      maze_, [](const Cell &cell) { return cell.right_wall; }, file);
  file << '\n';
  util::SaveCells(
      maze_, [](const Cell &cell) { return cell.bottom_wall; }, file);
  file.close();
  return true;
}

bool MazeManager::CustomCellEvent(int x, int y) {
  auto [scaled_row, scaled_col] = util::GetScaledCell(maze_);
  indices_[indices_count_++] = {y / scaled_row, x / scaled_col};
  // solve on second cell pick
  if (indices_count_ == 2) {
    maze_.Solve(indices_[0], indices_[1]);
    indices_count_ = 0;
    return true;
  }
  return false;
}

} // namespace mcg
