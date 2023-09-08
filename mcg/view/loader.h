#ifndef MAZECAVEGENERATOR_MCG_VIEW_LOADER_H
#define MAZECAVEGENERATOR_MCG_VIEW_LOADER_H

#include <QWidget>
#include <memory>
#include <utility>

#include "painter/painter.h"
#include "manager/manager.h"

namespace mcg {

class Loader : public QWidget {
  Q_OBJECT

 public:
  Loader(QWidget *parent = nullptr);
  ~Loader() = default;
  bool OpenFile(const QString &);
  bool SaveFile(const QString &);
  void GenerateMaze(size_t, size_t);
  void GenerateCave(size_t, size_t, size_t = 0, const Range & = {0, 0},
                    const Range & = {0, 0});
  void paintEvent(QPaintEvent *) override;
 public slots:
  void NextGenCave();
  void ChangeType(int);

 protected:
  void mousePressEvent(QMouseEvent *) override;

private:
 Cave cave_;
 Maze maze_;
 std::unique_ptr<IPainter> painter_;
 std::unique_ptr<IManager> manager_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_VIEW_LOADER_H
