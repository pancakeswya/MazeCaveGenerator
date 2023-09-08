#include "maze.h"

#include <algorithm>

#include "util/util.h"

namespace mcg {

bool Maze::Solve(Indices curr, const Indices &target) {
  for (auto &cell : *this) {
    cell.visited = false;
    cell.way = PathWay::kIdle;
  }
  return SolveRecursive(std::move(curr), target);
}

bool Maze::SolveRecursive(Indices curr, const Indices &target) {
  auto &[i, j] = curr;
  At(i, j).visited = true;
  if (curr == target) return true;
  if (j < GetCols() - 1 && !At(i, j).right_wall && !At(i, j + 1).visited &&
      SolveRecursive({i, j + 1}, target)) {
    At(i, j).way = PathWay::kRight;
    return true;
  }
  if (j > 0 && !At(i, j - 1).right_wall && !At(i, j - 1).visited &&
      SolveRecursive({i, j - 1}, target)) {
    At(i, j).way = PathWay::kLeft;
    return true;
  }
  if (i > 0 && !At(i - 1, j).bottom_wall && !At(i - 1, j).visited &&
      SolveRecursive({i - 1, j}, target)) {
    At(i, j).way = PathWay::kUp;
    return true;
  }
  if (i < GetRows() - 1 && !At(i, j).bottom_wall && !At(i + 1, j).visited &&
      SolveRecursive({i + 1, j}, target)) {
    At(i, j).way = PathWay::kDown;
    return true;
  }
  At(i, j).visited = false;
  return false;
}

void Maze::GenRightWalls(size_t row) {
  for (size_t j = 0; j < sets_.size() - 1; ++j) {
    bool is_wall = util::GenRandCond(0, 1);
    if (is_wall || sets_[j] == sets_[j + 1]) {
      At(row, j).right_wall = true;
    } else {
      std::replace_if(
          sets_.begin(), sets_.end(),
          [elem = sets_[j + 1]](size_t &set) { return set == elem; }, sets_[j]);
    }
  }
  At(row, sets_.size() - 1).right_wall = true;
}

void Maze::GenLowerWalls(size_t row) {
  for (size_t j = 0; j < sets_.size(); ++j) {
    bool is_wall = util::GenRandCond(0, 1);
    auto count = std::count(sets_.begin(), sets_.end(), sets_[j]);
    if (count != 1 && is_wall) {
      At(row, j).bottom_wall = true;
    }
  }
}

void Maze::FixLowerWalls(size_t row) {
  for (int i = 0; i < sets_.size(); ++i) {
    if (CountLowerWalls(sets_[i], row) == 0) {
      At(row, i).bottom_wall = false;
    }
  }
}

size_t Maze::CountLowerWalls(size_t elem, size_t row) {
  int count = 0;
  for (int i = 0; i < sets_.size(); ++i) {
    if (sets_[i] == elem && !At(row, i).bottom_wall) {
      ++count;
    }
  }
  return count;
}

void Maze::PrepareNewSets(size_t row, size_t &count) {
  for (size_t i = 0; i < sets_.size(); ++i) {
    if (At(row, i).bottom_wall) {
      sets_[i] = ++count;
    }
  }
}

void Maze::AddLastRow() {
  GenRightWalls(GetRows() - 1);
  for (size_t i = 0; i < sets_.size() - 1; ++i) {
    if (sets_[i] != sets_[i + 1]) {
      At(GetRows() - 1, i).right_wall = false;
      std::replace_if(
          sets_.begin(), sets_.end(),
          [elem = sets_[i + 1]](size_t &set) { return set == elem; }, sets_[i]);
    }
    At(GetRows() - 1, i).bottom_wall = true;
  }
  At(GetRows() - 1, GetCols() - 1).bottom_wall = true;
}

void Maze::Generate(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return;
  }
  Clear();
  SetRows(rows);
  SetCols(cols);
  sets_.resize(cols);
  size_t sets_count{cols};
  std::iota(sets_.begin(), sets_.end(), 1);
  for (size_t i = 0; i < rows - 1; ++i) {
    GenRightWalls(i);
    GenLowerWalls(i);
    FixLowerWalls(i);
    PrepareNewSets(i, sets_count);
  }
  AddLastRow();
  sets_.clear();
}

}  // namespace mcg
