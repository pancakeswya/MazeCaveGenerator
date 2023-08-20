#ifndef VIEW_H_
#define VIEW_H_

#include "maze.h"
#include "cave.h"

#include <QWidget>

namespace mcg {

using ScaledSize = std::pair<int,int>;

class IView {
 public:
  virtual bool OpenFile(const QString &) = 0;
  virtual bool SaveFile(const QString &) = 0;
  virtual void Draw(QWidget *) = 0;
  virtual bool SolveOnMouseEvent(QMouseEvent *) = 0;
  virtual ~IView() = default;
};

class ViewSize {
 public:
  ViewSize(int width, int height)
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

class CaveView : public IView, public ViewSize {
 public:
  CaveView(int width, int height);
  bool OpenFile(const QString &) override;
  bool SaveFile(const QString &) override;
  bool SolveOnMouseEvent(QMouseEvent *) override;
  void Generate(size_t rows, size_t cols, size_t life_chance, const Range& live, const Range& born);
  void NextGeneration() noexcept;
  void Draw(QWidget *) override;
 private:
  [[nodiscard]] ScaledSize GetScaledCell() const noexcept;
  Cave cave_;
};

inline CaveView::CaveView(int width, int height) : ViewSize(width, height) {}

inline MazeView::MazeView(int width, int height) : ViewSize(width, height) {}

inline void MazeView::Generate(size_t rows, size_t cols) {
  maze_.Generate(rows, cols);
}

inline void CaveView::Generate(size_t rows, size_t cols, size_t life_chance, const Range& live, const Range& born) {
  cave_.Generate(rows, cols, life_chance, live, born);
}

inline void CaveView::NextGeneration() noexcept {
  cave_.NextGeneration();
}

} // namespace mcg

#endif // VIEW_H_
