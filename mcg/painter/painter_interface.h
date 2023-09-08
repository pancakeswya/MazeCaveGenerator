#ifndef MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_INTERFACE_H_
#define MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_INTERFACE_H_

#include <QWidget>

namespace mcg {

class IPainter {
public:
  virtual void Draw(QWidget *) = 0;
  virtual ~IPainter() = default;
};

} // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_PAINTER_PAINTER_INTERFACE_H_