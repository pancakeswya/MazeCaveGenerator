#include "model/serializer.h"

#include <fstream>
#include <functional>

namespace mcg {

namespace {

template <typename Tp, typename Pred>
void SaveWalls(const Matrix<Tp>& mcg, Pred GetWalls, std::ofstream& os) {
  for (size_t i = 0; i < mcg.GetRows(); ++i) {
    for (size_t j = 0; j < mcg.GetCols(); ++j) {
      os << GetWalls(mcg[i][j]);
      if (j != mcg.GetCols() - 1) {
        os << ' ';
      }
    }
    os << '\n';
  }
}

}  // namespace

namespace maze {

bool Marshal(const WallsMap& maze_map, const std::string& path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << maze_map.GetRows() << ' ' << maze_map.GetCols() << ' ' << '\n';
  SaveWalls(
      maze_map, [](const Walls& cell) -> int { return cell.right_wall; }, file);
  file << '\n';
  SaveWalls(
      maze_map, [](const Walls& cell) -> int { return cell.bottom_wall; },
      file);
  return true;
}

std::pair<bool, WallsMap> Unmarshal(const std::string& path) {
  std::ifstream file(path.data(), std::ifstream::binary);
  if (!file.is_open()) {
    return {false, {}};
  }
  size_t rows, cols;
  file >> rows >> cols;
  maze::WallsMap maze_map(rows, cols);
  for (Walls& walls : maze_map) {
    file >> walls.right_wall;
  }
  char c;
  do {
    file.get(c);
  } while (file.good() && c != '\n');
  for (Walls& walls : maze_map) {
    file >> walls.bottom_wall;
  }
  return {true, maze_map};
}

}  // namespace maze

namespace cave {

bool Marshal(const WallsMap& cave_map, const std::string& path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << cave_map.GetRows() << ' ' << cave_map.GetCols() << ' ' << '\n';
  SaveWalls(
      cave_map, [](Walls walls) -> int { return walls; }, file);
  return true;
}

std::pair<bool, WallsMap> Unmarshal(const std::string& path) {
  std::ifstream file(path.data(), std::ifstream::binary);
  if (!file.is_open()) {
    return {false, {}};
  }
  size_t rows, cols;
  file >> rows >> cols;
  cave::WallsMap walls_map(rows, cols);
  for (Walls& walls : walls_map) {
    file >> walls;
  }
  return {true, walls_map};
}

}  // namespace cave

}  // namespace mcg