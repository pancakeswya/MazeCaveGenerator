#ifndef MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_H_
#define MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_H_

#include <QWidget>

#include "lib/cave/cave.h"
#include "lib/maze/maze.h"

namespace mcg {

class IPainter {
 public:
  virtual void Draw(QWidget *) = 0;
  virtual ~IPainter() = default;
};

class CavePainter : public IPainter {
 public:
  CavePainter(const Cave& cave);
  void Draw(QWidget* widget) override;

 private:
  const Cave& cave_;
};

class MazePainter : public IPainter {
 public:
  MazePainter(const Maze &maze);
  void Draw(QWidget *widget) override;

 private:
  const Maze &maze_;
};

inline CavePainter::CavePainter(const Cave &cave) : cave_(cave) {}

inline MazePainter::MazePainter(const Maze &maze) : maze_(maze) {}

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_H_
