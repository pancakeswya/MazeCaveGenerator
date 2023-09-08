#ifndef MAZECAVEGENERATOR_MCG_MANAGER_MANAGER_INTERFACE_H_
#define MAZECAVEGENERATOR_MCG_MANAGER_MANAGER_INTERFACE_H_

#include <string_view>

namespace mcg {

class IManager {
 public:
  virtual bool Open(std::string_view path) = 0;
  virtual bool Save(std::string_view path) = 0;
  virtual bool CustomCellEvent(int x, int y) = 0;
  virtual ~IManager() = default;
};


} // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_MANAGER_MANAGER_INTERFACE_H_