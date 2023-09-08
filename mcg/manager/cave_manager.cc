#include "cave_manager.h"

#include "util/util.h"

namespace mcg {

bool CaveManager::Open(std::string_view path) {
  std::ifstream file(path.data(), std::ifstream::binary);
  if (!file.is_open()) {
    return false;
  }
  size_t rows, cols;
  file >> rows >> cols;
  cave_.SetRows(rows);
  cave_.SetCols(cols);
  for (auto &cell : cave_) {
    file >> cell;
  }
  return true;
}

bool CaveManager::Save(std::string_view path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << cave_.GetRows() << ' ' << cave_.GetCols() << ' ' << '\n';
  util::SaveCells(
      cave_, [](int &cell) { return cell; }, file);
  return true;
}

bool CaveManager::CustomCellEvent(int x, int y) {
  if (!cave_.GetCols() || !cave_.GetRows()) {
    return false;
  }
  auto [scaled_row, scaled_col] = util::GetScaledCell(cave_);
  cave_.At(y / scaled_row, x / scaled_col) = 1;
  return true;
}

} // namespace mcg

