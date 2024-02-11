#ifndef MAZECAVEGENERATOR_SRC_MODEL_CAVE_MODEL_H_
#define MAZECAVEGENERATOR_SRC_MODEL_CAVE_MODEL_H_

#include <string>
#include <utility>

#include "base/types.h"

namespace mcg {

class CaveModel {
 public:
  bool Load(const std::string& path);
  bool Save(const std::string& path);

  void Generate(const cave::Params& params);
  void GenerateNext(const cave::Params& params);

  [[nodiscard]] const cave::WallsMap& GetMap() const noexcept;

 private:
  cave::WallsMap cave_map_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_MODEL_CAVE_MODEL_H_