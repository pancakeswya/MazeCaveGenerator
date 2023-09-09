#ifndef MAZECAVEGENERATOR_MCG_VIEW_MANAGER_H_
#define MAZECAVEGENERATOR_MCG_VIEW_MANAGER_H_

#include <string_view>

#include "lib/cave/cave.h"
#include "lib/maze/maze.h"

namespace mcg {

class IManager {
 public:
  virtual bool Open(std::string_view path) = 0;
  virtual bool Save(std::string_view path) = 0;
  virtual bool Event(int x, int y) = 0;
  virtual ~IManager() = default;
};

class CaveManager : public IManager {
 public:
  CaveManager(Cave& cave);
  bool Open(std::string_view path) override;
  bool Save(std::string_view path) override;
  bool Event(int x, int y) override;

 private:
  Cave& cave_;
};

class MazeManager : public IManager {
 public:
  MazeManager(Maze& maze);
  bool Open(std::string_view) override;
  bool Save(std::string_view) override;
  bool Event(int x, int y) override;

 private:
  int indices_count_{};
  Indices indices_[2];
  Maze& maze_;
};

inline CaveManager::CaveManager(Cave &cave) : cave_(cave) {}

inline MazeManager::MazeManager(Maze& maze) : maze_(maze) {}

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_VIEW_MANAGER_H_