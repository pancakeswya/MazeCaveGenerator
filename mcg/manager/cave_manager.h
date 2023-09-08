#ifndef MAZECAVEGENERATOR_MCG_MANAGER_CAVE_MANAGER_H_
#define MAZECAVEGENERATOR_MCG_MANAGER_CAVE_MANAGER_H_

#include "manager_interface.h"
#include "lib/cave/cave.h"

namespace mcg {

class CaveManager : public IManager {
 public:
  CaveManager(Cave& cave);
  bool Open(std::string_view path) override;
  bool Save(std::string_view path) override;
  bool CustomCellEvent(int x, int y) override;

 private:
  Cave& cave_;
};

inline CaveManager::CaveManager(Cave& cave) : cave_(cave) {}

} // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_MANAGER_CAVE_MANAGER_H_