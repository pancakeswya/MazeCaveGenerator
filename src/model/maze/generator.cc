#include "model/maze/generator.h"

#include <algorithm>
#include <numeric>
#include <vector>

#include "base/util.h"

namespace mcg::maze {

namespace {

void GenRightWalls(WallsMap& walls_map, std::vector<size_t>& sets, size_t row) {
  for (size_t j = 0; j < sets.size() - 1; ++j) {
    bool is_wall = util::GenRandomNum(0, 1);
    if (is_wall || sets[j] == sets[j + 1]) {
      walls_map[row][j].right_wall = true;
    } else {
      std::replace_if(
          sets.begin(), sets.end(),
          [=](size_t set) { return set == sets[j + 1]; }, sets[j]);
    }
  }
  walls_map[row][sets.size() - 1].right_wall = true;
}

void GenLowerWalls(WallsMap& walls_map, std::vector<size_t> sets, size_t row) {
  for (size_t i = 0; i < sets.size(); ++i) {
    bool is_wall = util::GenRandomNum(0, 1);
    if (is_wall && std::count(sets.begin(), sets.end(), sets[i]) != 1) {
      walls_map[row][i].bottom_wall = true;
    }
  }
}

size_t CountLowerWalls(WallsMap& walls_map, std::vector<size_t>& sets,
                       size_t elem, size_t row) {
  size_t count = 0;
  for (size_t i = 0; i < sets.size(); ++i) {
    if (sets[i] == elem && !walls_map[row][i].bottom_wall) {
      ++count;
    }
  }
  return count;
}

void FixLowerWalls(WallsMap& walls_map, std::vector<size_t> sets, size_t row) {
  for (size_t i = 0; i < sets.size(); ++i) {
    if (!CountLowerWalls(walls_map, sets, sets[i], row)) {
      walls_map[row][i].bottom_wall = false;
    }
  }
}

void PrepareNewSets(WallsMap& walls_map, std::vector<size_t>& sets, size_t row,
                    size_t& count) {
  for (size_t i = 0; i < sets.size(); ++i) {
    if (walls_map[row][i].bottom_wall) {
      sets[i] = ++count;
    }
  }
}

void AddLastRow(WallsMap& walls_map, std::vector<size_t>& sets) {
  GenRightWalls(walls_map, sets, walls_map.GetRows() - 1);
  for (size_t i = 0; i < sets.size() - 1; ++i) {
    if (sets[i] != sets[i + 1]) {
      walls_map[walls_map.GetRows() - 1][i].right_wall = false;
      std::replace_if(
          sets.begin(), sets.end(),
          [=](size_t& set) { return set == sets[i + 1]; }, sets[i]);
    }
    walls_map[walls_map.GetRows() - 1][i].bottom_wall = true;
  }
  walls_map[walls_map.GetRows() - 1][walls_map.GetCols() - 1].bottom_wall =
      true;
}

}  // namespace

WallsMap Generate(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return {};
  }
  WallsMap walls_map(rows, cols);
  std::vector<size_t> sets(cols);

  std::iota(sets.begin(), sets.end(), 1);
  for (size_t i = 0; i < rows - 1; ++i) {
    GenRightWalls(walls_map, sets, i);
    GenLowerWalls(walls_map, sets, i);
    FixLowerWalls(walls_map, sets, i);
    PrepareNewSets(walls_map, sets, i, cols);
  }
  AddLastRow(walls_map, sets);
  return walls_map;
}

}  // namespace mcg::maze