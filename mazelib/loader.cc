#include "loader.h"

#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

namespace mcg {

Loader::Loader(QWidget *parent)
    : QWidget(parent), type_(LoadType::kStart) {}

void Loader::ChangeType(int type) {
    type_ = LoadType(type);
}

bool Loader::OpenFile(const QString &path) {
  bool is_loaded;
  if (type_ == LoadType::kMaze) {
    is_loaded = maze_.ReadFile(path.toStdString());
  } else {
    is_loaded = cave_.ReadFile(path.toStdString());
  }
  if (is_loaded) {
    update();
  }
  return is_loaded;
}

void Loader::GenerateMaze(size_t rows, size_t cols) {
  maze_.Generate(rows, cols);
  update();
}

void Loader::DrawCave() {
  QPainter painter;
  painter.begin(this);
  auto scale_row = float(height()) / cave_.GetRows();
  auto scale_col = float(width()) / cave_.GetCols();
  for (size_t i = 0; i < cave_.GetRows(); ++i) {
    for (size_t j = 0; j < cave_.GetCols(); ++j) {
      if (cave_[i][j] == 1) {
        painter.fillRect(j * scale_col, i * scale_row, scale_col, scale_row, Qt::black);
      }
    }
  }
  painter.end();
}

void Loader::DrawMaze() {
  QPainter painter;
  painter.begin(this);
  auto scale_row = float(height() - 2) / maze_.GetRows();
  auto scale_col = float(width() - 2) / maze_.GetCols();
  painter.fillRect(0, 0, width(), 2, Qt::black);
  painter.fillRect(0, 0, 2, height(), Qt::black);
  for (size_t i = 0; i < maze_.GetRows(); ++i) {
    for (size_t j = 0; j < maze_.GetCols(); ++j) {
      if (maze_[i][j].right_wall) {
        for (size_t k = i * scale_row; k < (i + 1) * scale_row; ++k) {
          painter.fillRect((j + 1) * scale_col, k, 2, 2, Qt::black);
        }
      }
      if (maze_[i][j].bottom_wall) {
        for (size_t k = j * scale_col; k < (j + 1) * scale_col; ++k) {
          painter.fillRect(k, (i + 1) * scale_row, 2, 2, Qt::black);
        }
      }
    }
  }
  painter.end();
}

void Loader::mousePressEvent(QMouseEvent *event)
{
    if (type_ != LoadType::kMaze) {
        return;
    }
    if (event->button() == Qt::LeftButton){

    }
}

void Loader::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton){
        qDebug() << "right button is released";
    }
}

void Loader::paintEvent(QPaintEvent *) {
  if (type_ == LoadType::kCave) {
    DrawCave();
  } else if (type_ == LoadType::kMaze) {
    DrawMaze();
  }
}

} // namespace mcg
