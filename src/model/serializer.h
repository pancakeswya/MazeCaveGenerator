#ifndef MAZECAVEGENERATOR_SRC_MODEL_SERIALIZER_H_
#define MAZECAVEGENERATOR_SRC_MODEL_SERIALIZER_H_

#include "base/types.h"

#include <string>

namespace mcg {

namespace maze {

bool Marshal(const WallsMap& maze_map, const std::string& path);
std::pair<bool, WallsMap> Unmarshal(const std::string& path);

} // namespace maze

namespace cave {

bool Marshal(const WallsMap& cave_map, const std::string& path);
std::pair<bool, WallsMap> Unmarshal(const std::string& path);

} // namespace cave


} // namespace mcg

#endif // MAZECAVEGENERATOR_SRC_MODEL_SERIALIZER_H_
