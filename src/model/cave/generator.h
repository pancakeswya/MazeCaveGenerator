#ifndef MAZECAVEGENERATOR_SRC_MODEL_CAVE_GENERATOR_H_
#define MAZECAVEGENERATOR_SRC_MODEL_CAVE_GENERATOR_H_

#include "base/types.h"

namespace mcg::cave {

extern WallsMap Generate(const Params& params);
extern WallsMap GenerateNext(const WallsMap& walls_map, const Params& params);

}  // namespace mcg::cave

#endif  // MAZECAVEGENERATOR_SRC_MODEL_CAVE_GENERATOR_H_