#ifndef MAZECAVEGENERATOR_INCLUDES_VIEW_VIEW_INTERFACE_H_
#define MAZECAVEGENERATOR_INCLUDES_VIEW_VIEW_INTERFACE_H_

#include <QWidget>

namespace mcg {

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

} // namespace mcg

#endif // VIEW_INTERFACE_H_
