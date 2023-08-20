#ifndef MAZECAVEGENERATOR_SRC_VIEW_MAZE_VIEW_H_
#define MAZECAVEGENERATOR_SRC_VIEW_MAZE_VIEW_H_

#include "../model/maze.h"
#include "defs.h"
#include "view_interface.h"

namespace mcg {

class MazeView : public IView, public ViewSize {
 public:
  MazeView(int width, int height);
  bool OpenFile(const QString &) override;
  bool SaveFile(const QString &) override;
  bool SolveOnMouseEvent(QMouseEvent *) override;
  void Draw(QWidget *) override;
  void Generate(size_t rows, size_t cols);
  bool Solve(Indices curr, const Indices &target);

 private:
  [[nodiscard]] ScaledSize GetScaledCell(int w, int h) const noexcept;
  int indices_count_{};
  Indices indices_[2]{};
  Maze maze_;
};

inline MazeView::MazeView(int width, int height) : ViewSize(width, height) {}

inline void MazeView::Generate(size_t rows, size_t cols) {
  maze_.Generate(rows, cols);
}

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_VIEW_MAZE_VIEW_H_
