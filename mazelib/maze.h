#ifndef MAZE_H_
#define MAZE_H_

#include "matrix.h"
#include <string>

namespace mcg {

enum class PathWay : short int {
  kIdle,
  kUp,
  kDown,
  kRight,
  kLeft
};

using Indices = std::pair<int, int>;

struct Cell {
  bool right_wall{};
  bool bottom_wall{};
  bool visited{};
  PathWay way{};
};

class Maze : public Matrix<Cell> {
 public:
  void Generate(size_t rows, size_t cols);
  bool Solve(Indices curr, const Indices &target);
 private:
  std::vector<size_t> sets_;
  bool SolveRecursive(Indices curr, const Indices &target);
  void GenRightWalls(size_t row);
  void GenLowerWalls(size_t row);
  void FixLowerWalls(size_t row);
  size_t CountLowerWalls(size_t elem, size_t row);
  void PrepareNewSets(size_t row, size_t &count);
  void AddLastRow();
};

} // namespace mcg

#endif // MAZE_H_
