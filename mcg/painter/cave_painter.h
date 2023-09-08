#ifndef MAZECAVEGENERATOR_MCG_PAINTER_CAVE_PAINTER_H_
#define MAZECAVEGENERATOR_MCG_PAINTER_CAVE_PAINTER_H_

#include "painter_interface.h"
#include "lib/cave/cave.h"

namespace mcg {

class CavePainter : public IPainter {
 public:
  CavePainter(const Cave& cave);
  void Draw(QWidget* widget) override;

 private:
  const Cave& cave_;
};

inline CavePainter::CavePainter(const Cave& cave) : cave_(cave) {}

} // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_PAINTER_CAVE_PAINTER_H_