#ifndef MAZECAVEGENERATOR_SRC_PAINTER_PAINTER_H_
#define MAZECAVEGENERATOR_SRC_PAINTER_PAINTER_H_

#include <QWidget>

#include "base/types.h"

namespace mcg {

namespace maze {

extern void Draw(QWidget *widget, const WallsMap& walls_map, const SolutionMap& solution_map);

} // namespace maze

namespace cave {

extern void Draw(QWidget *widget, const WallsMap& walls_map);

} // namespace cave

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_PAINTER_PAINTER_H_
