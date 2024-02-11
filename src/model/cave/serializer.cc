#include "model/cave/serializer.h"

#include "base/util.h"

namespace mcg::cave {

bool Marshal(const WallsMap& cave_map, const std::string& path) {
  std::ofstream file(path.data());
  if (!file) {
    return false;
  }
  file << cave_map.GetRows() << ' ' << cave_map.GetCols() << ' ' << '\n';
  util::SaveWalls(
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

}  // namespace mcg::cave