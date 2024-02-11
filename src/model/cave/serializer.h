#ifndef MAZECAVEGENERATOR_SRC_MODEL_CAVE_SERIALIZER_H_
#define MAZECAVEGENERATOR_SRC_MODEL_CAVE_SERIALIZER_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg::cave {

extern bool Marshal(const WallsMap& cave_map, const std::string& path);
extern std::pair<bool, WallsMap> Unmarshal(const std::string& path);

}  // namespace mcg::cave

#endif  // MAZECAVEGENERATOR_SRC_MODEL_CAVE_SERIALIZER_H_