#include "model/maze/serializer.h"

#include "base/util.h"

namespace mcg::maze {

bool Marshal(const WallsMap& maze_map, const std::string& path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << maze_map.GetRows() << ' ' << maze_map.GetCols() << ' ' << '\n';
  util::SaveWalls(
      maze_map, [](const Walls& cell) -> int { return cell.right_wall; }, file);
  file << '\n';
  util::SaveWalls(
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

}  // namespace mcg::maze