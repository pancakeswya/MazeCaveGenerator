#ifndef VIEW_H_
#define VIEW_H_

#include "maze.h"
#include "cave.h"

#include <QWidget>

namespace mcg {

class ISize {
 public:
  ISize(int width, int height)
      : width_(width), height_(height) {}

  [[nodiscard]] size_t GetWidth() const noexcept {
    return width_;
  }

  [[nodiscard]] size_t GetHeight() const noexcept {
    return height_;
  }
 private:
  size_t width_, height_;
};

class IView {
 public:
  virtual bool OpenFile(const QString &) = 0;
  virtual bool SaveFile(const QString &) = 0;
  virtual void Draw(QWidget *) = 0;
  virtual bool SolveOnMouseEvent(QMouseEvent *) = 0;
  virtual ~IView() = default;
};

class MazeView : public IView, public ISize {
 public:
  MazeView(int width, int height);
  bool OpenFile(const QString &) override;
  bool SaveFile(const QString &) override;
  bool SolveOnMouseEvent(QMouseEvent *) override;
  void Draw(QWidget *) override;
  void Generate(size_t rows, size_t cols);
  bool Solve(Indices curr, const Indices &target);
 private:
  int indices_count_{};
  Indices indices_[2]{};
  Maze maze_;
};

class CaveView : public IView, public ISize {
 public:
  CaveView(int width, int height);
  bool OpenFile(const QString &) override;
  bool SaveFile(const QString &) override;
  bool SolveOnMouseEvent(QMouseEvent *) override;
  void Draw(QWidget *) override;
 private:
  Cave cave_;
};

inline CaveView::CaveView(int width, int height) : ISize(width, height) {}

inline MazeView::MazeView(int width, int height) : ISize(width, height) {}

inline void MazeView::Generate(size_t rows, size_t cols) {
  maze_.Generate(rows, cols);
}

} // namespace mcg

#endif // VIEW_H_
