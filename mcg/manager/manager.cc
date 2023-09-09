#include "manager.h"
#include "util/util.h"

#include <fstream>

namespace mcg {

namespace {

template <typename Tp, typename Pred>
void SaveCells(Matrix<Tp> &mcg, Pred GetCell, std::ofstream &os) {
  for (size_t i = 0; i < mcg.GetRows(); ++i) {
    for (size_t j = 0; j < mcg.GetCols(); ++j) {
      os << GetCell(mcg[i][j]);
      if (j != mcg.GetCols() - 1) {
        os << ' ';
      }
    }
    os << '\n';
  }
}

} // namespace

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
  SaveCells(
      cave_, [](int &cell) { return cell; }, file);
  return true;
}

bool CaveManager::Event(int x, int y) {
  if (!cave_.GetCols() || !cave_.GetRows()) {
    return false;
  }
  auto [scaled_row, scaled_col] = util::GetScaledCell(cave_);
  cave_.At(y / scaled_row, x / scaled_col) = 1;
  return true;
}

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
  SaveCells(
      maze_, [](const Cell &cell) { return cell.right_wall; }, file);
  file << '\n';
  SaveCells(
      maze_, [](const Cell &cell) { return cell.bottom_wall; }, file);
  file.close();
  return true;
}

bool MazeManager::Event(int x, int y) {
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
