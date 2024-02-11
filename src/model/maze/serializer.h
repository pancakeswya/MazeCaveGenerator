#ifndef MAZECAVEGENERATOR_SRC_MODEL_MAZE_SERIALIZER_H_
#define MAZECAVEGENERATOR_SRC_MODEL_MAZE_SERIALIZER_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg::maze {

extern bool Marshal(const WallsMap& maze_map, const std::string& path);
extern std::pair<bool, WallsMap> Unmarshal(const std::string& path);

}  // namespace mcg::maze

#endif  // MAZECAVEGENERATOR_SRC_MODEL_MAZE_SERIALIZER_H_