#ifndef MAZECAVEGENERATOR_MCG_PAINTER_MAZE_PAINTER_H_
#define MAZECAVEGENERATOR_MCG_PAINTER_MAZE_PAINTER_H_

#include "painter_interface.h"
#include "lib/maze/maze.h"

namespace mcg {

class MazePainter : public IPainter {
 public:
  MazePainter(const Maze &maze);
  void Draw(QWidget *widget) override;

 private:
  const Maze &maze_;
};

inline MazePainter::MazePainter(const Maze &maze) : maze_(maze) {}

} // namespace mcg


#endif  // MAZECAVEGENERATOR_MCG_PAINTER_MAZE_PAINTER_H_