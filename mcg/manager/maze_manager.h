#ifndef MAZECAVEGENERATOR_MCG_MANAGER_MAZE_MANAGER_H_
#define MAZECAVEGENERATOR_MCG_MANAGER_MAZE_MANAGER_H_

#include "manager_interface.h"
#include "lib/maze/maze.h"

namespace mcg {

class MazeManager : public IManager {
 public:
  MazeManager(Maze& maze);
  bool Open(std::string_view) override;
  bool Save(std::string_view) override;
  bool CustomCellEvent(int x, int y) override;

 private:
  int indices_count_{};
  Indices indices_[2];
  Maze& maze_;
};

inline MazeManager::MazeManager(Maze& maze) : maze_(maze) {}

} // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_MANAGER_MAZE_MANAGER_H_