#ifndef MAZECAVEGENERATOR_SRC_VIEW_LOADER_H
#define MAZECAVEGENERATOR_SRC_VIEW_LOADER_H

#include <QWidget>

#include "view.h"

namespace mcg {

class Loader : public QWidget {
  Q_OBJECT

 public:
  Loader(QWidget *parent = nullptr);
  ~Loader();
  bool OpenFile(const QString &);
  bool SaveFile(const QString &);
  void GenerateMaze(size_t, size_t);
  void GenerateCave(size_t, size_t, size_t = 0, const Range & = {0, 0},
                    const Range & = {0, 0});
  void paintEvent(QPaintEvent *) override;
 public slots:
  void NextGenCave() noexcept;
  void ChangeType(int);

 protected:
  void mousePressEvent(QMouseEvent *) override;

 private:
  IView *view_ptr_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_VIEW_LOADER_H
