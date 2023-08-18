#include "cave.h"

#include <fstream>

namespace mcg {

bool Cave::ReadFile(std::string_view path) {
  std::ifstream file(path.data(), std::ifstream::binary);
  if (!file.is_open()) {
    return false;
  }
  size_t rows, cols;
  file >> rows >> cols;
  SetRows(rows);
  SetCols(cols);
  for (auto& cell : *this) {
    file >> cell;
  }
  return true;
}

void Cave::Generate(size_t rows, size_t cols) {
  (void) rows;
  (void) cols;
}

} // namespace mcg
