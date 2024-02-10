#include "model/maze/solver.h"

namespace mcg::maze {

namespace {

bool SolveRecursive(SolutionMap& solution_map, const WallsMap& walls_map, Indices curr, const Indices &target) {
  auto [i, j] = curr;
  solution_map[i][j].visited = true;
  if (curr == target) {
    return true;
  }
  if (j < walls_map.GetCols() - 1 &&
     !walls_map[i][j].right_wall &&
     !solution_map[i][j + 1].visited &&
      SolveRecursive(solution_map, walls_map, {i, j + 1}, target)) {
    solution_map[i][j].vector = Vector::kRight;
    return true;
  }
  if (j > 0 && !walls_map[i][j - 1].right_wall &&
     !solution_map[i][j - 1].visited &&
      SolveRecursive(solution_map, walls_map, {i, j - 1}, target)) {
    solution_map[i][j].vector = Vector::kLeft;
    return true;
  }
  if (i > 0 && !walls_map[i - 1][j].bottom_wall &&
     !solution_map[i - 1][j].visited &&
      SolveRecursive(solution_map, walls_map, {i - 1, j}, target)) {
    solution_map[i][j].vector = Vector::kUp;
    return true;
  }
  if (i < walls_map.GetRows() - 1 &&
     !walls_map[i][j].bottom_wall && !solution_map[i + 1][j].visited &&
      SolveRecursive(solution_map, walls_map, {i + 1, j}, target)) {
    solution_map[i][j].vector = Vector::kDown;
    return true;
  }
  solution_map[i][j].visited = false;
  return false;
}

} // namespace

std::pair<bool, SolutionMap> Solve(const WallsMap& walls_map, const Indices& curr, const Indices& target) {
  SolutionMap solution_map;
  bool solved = SolveRecursive(solution_map, walls_map, curr, target);
  return {solved, solution_map};
}

} // namespace mcg::maze