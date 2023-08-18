#include "loader.h"

#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

namespace mcg {

enum DrawingSizes {
  kCaveSize = 500,
  // +2 for up and left borders
  kMazeSize = 502
};

Loader::Loader(QWidget *parent)
    : QWidget(parent), view_ptr_(new CaveView(kCaveSize, kMazeSize)) {}

Loader::~Loader() {
  delete view_ptr_;
}

void Loader::ChangeType(int type) {
  delete view_ptr_;
  if (type) {
    view_ptr_ = new MazeView(kMazeSize, kMazeSize);
  } else {
    view_ptr_ = new CaveView(kCaveSize, kCaveSize);
  }
}

bool Loader::OpenFile(const QString &path) {
  bool is_loaded = view_ptr_->OpenFile(path);
  if (is_loaded) {
    update();
  }
  return is_loaded;
}

bool Loader::SaveFile(const QString &path) {
  return view_ptr_->SaveFile(path);
}

void Loader::GenerateMaze(size_t rows, size_t cols) {
  static_cast<MazeView *>(view_ptr_)->Generate(rows, cols);
  update();
}

void Loader::mousePressEvent(QMouseEvent *event) {
  bool is_solved = view_ptr_->SolveOnMouseEvent(event);
  if (is_solved) {
    update();
  }
}

void Loader::paintEvent(QPaintEvent *) {
  view_ptr_->Draw(this);
}

} // namespace mcg
