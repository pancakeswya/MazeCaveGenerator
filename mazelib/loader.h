#ifndef LOADER_H
#define LOADER_H

#include "maze.h"
#include "cave.h"

#include <QWidget>

namespace mcg {

enum class LoadType : int {
  kCave,
  kMaze,
  kStart
};

class Loader : public QWidget {
  Q_OBJECT

 public:
  Loader(QWidget *parent = nullptr);
  ~Loader() = default;
  bool OpenFile(const QString &);
  void GenerateMaze(size_t, size_t);
  void DrawCave();
  void DrawMaze();
  void paintEvent(QPaintEvent *) override;
public slots:
  void ChangeType(int);
 protected:
  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
 private:
  int indices_count_{};
  Indices indices_[2]{};
  Maze maze_;
  Cave cave_;
  LoadType type_{};
};

} // namespace mcg

#endif // LOADER_H
