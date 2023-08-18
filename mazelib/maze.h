#ifndef MAZE_H_
#define MAZE_H_

#include "matrix.h"
#include <string>

namespace mcg {

using Indices = std::pair<int, int>;

struct Cell {
  bool right_wall{};
  bool bottom_wall{};
  bool visited{};
};

class Maze : public Matrix<Cell> {
 public:
  bool ReadFile(std::string_view path);
  void Generate(size_t rows, size_t cols);
  bool Solve(Indices curr, const Indices &target);
  const std::vector<Indices> &GetSolvePath() const
  noexcept;
 private:
  std::vector<size_t> sets_;
  std::vector<Indices> solve_path_;
  void GenRightWalls(size_t row);
  void GenLowerWalls(size_t row);
  void FixLowerWalls(size_t row);
  size_t CountLowerWalls(size_t elem, size_t row);
  void PrepareNewSets(size_t row, size_t &count);
  void AddLastRow();
};

inline const std::vector<Indices> &Maze::GetSolvePath() const noexcept {
  return solve_path_;
}

} // namespace mcg

#endif // MAZE_H_
