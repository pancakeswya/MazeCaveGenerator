#ifndef LOADER_H
#define LOADER_H

#include "view.h"

#include <QWidget>

namespace mcg {

class Loader : public QWidget {
  Q_OBJECT

 public:
  Loader(QWidget *parent = nullptr);
  ~Loader();
  bool OpenFile(const QString &);
  bool SaveFile(const QString &);
  void GenerateMaze(size_t, size_t);
  void paintEvent(QPaintEvent *) override;
public slots:
  void ChangeType(int);
 protected:
  void PushIndices(int, int);
  void mousePressEvent(QMouseEvent*) override;
 private:
  IView* view_ptr_;
};

} // namespace mcg

#endif // LOADER_H
