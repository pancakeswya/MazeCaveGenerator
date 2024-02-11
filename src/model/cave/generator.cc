#include "model/cave/generator.h"

#include <algorithm>

#include "base/util.h"

namespace mcg::cave {

namespace {

inline int CheckNeighbour(const WallsMap& walls_map, size_t row,
                          size_t col) noexcept {
  if (row >= walls_map.GetRows() || col >= walls_map.GetCols()) {
    return true;
  }
  return walls_map[row][col];
}

inline size_t CountNeighbours(const WallsMap& walls_map, size_t row,
                              size_t col) {
  return CheckNeighbour(walls_map, row, col - 1) +
         CheckNeighbour(walls_map, row, col + 1) +
         CheckNeighbour(walls_map, row - 1, col) +
         CheckNeighbour(walls_map, row + 1, col) +
         CheckNeighbour(walls_map, row - 1, col - 1) +
         CheckNeighbour(walls_map, row - 1, col + 1) +
         CheckNeighbour(walls_map, row + 1, col - 1) +
         CheckNeighbour(walls_map, row + 1, col + 1);
}

WallsMap GenerateWalls(const WallsMap& walls_map, const Params& params) {
  WallsMap result = walls_map;
  for (size_t row = 0; row != walls_map.GetRows(); ++row) {
    for (size_t col = 0; col != walls_map.GetCols(); ++col) {
      size_t count = CountNeighbours(walls_map, row, col);
      if (walls_map[row][col] && (count < params.live_limit.first ||
                                  count > params.live_limit.second)) {
        result[row][col] = 0;
      } else if (!walls_map[row][col] && count >= params.born_limit.first &&
                 count <= params.born_limit.second) {
        result[row][col] = 1;
      }
    }
  }
  return result;
}

}  // namespace

WallsMap Generate(const Params& params) {
  WallsMap walls_map(params.rows, params.cols);
  if (!params.rows || !params.cols || !params.life_chance) {
    return walls_map;
  }
  std::generate(walls_map.begin(), walls_map.end(), [=] {
    return util::GenRandomNum(0, 100) <= params.life_chance;
  });
  return GenerateWalls(walls_map, params);
}

WallsMap GenerateNext(const WallsMap& walls_map, const Params& params) {
  if (!walls_map.GetCols() || !walls_map.GetRows()) {
    return {};
  }
  return GenerateWalls(walls_map, params);
}

}  // namespace mcg::cave
