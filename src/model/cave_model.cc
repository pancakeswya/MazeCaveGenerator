#include "model/cave_model.h"

#include "model/cave/generator.h"
#include "model/cave/serializer.h"

namespace mcg {

bool CaveModel::Load(const std::string& path) {
  auto [ok, cave_map] = cave::Unmarshal(path);
  cave_map_ = std::move(cave_map);
  return ok;
}

bool CaveModel::Save(const std::string& path) {
  return cave::Marshal(cave_map_, path);
}

void CaveModel::Generate(const cave::Params& params) {
  cave_map_ = cave::Generate(params);
}

void CaveModel::GenerateNext(const cave::Params& params) {
  cave_map_ = cave::GenerateNext(cave_map_, params);
}

const cave::WallsMap& CaveModel::GetMap() const noexcept { return cave_map_; }

}  // namespace mcg