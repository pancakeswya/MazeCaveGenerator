#include "view/loader.h"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

#include "base/util.h"

namespace mcg {

Loader::Loader(QWidget* parent) noexcept
    : controller_(), QWidget(parent), type_() {}

void Loader::SetController(Controller* controller) noexcept {
  controller_ = controller;
}

void Loader::SetType(int type) { type_ = type; }

size_t Loader::GetRows() const noexcept {
  if (type_ == GenerateType::kMaze) {
    return maze_map_.GetRows();
  }
  return cave_map_.GetRows();
}

size_t Loader::GetCols() const noexcept {
  if (type_ == GenerateType::kMaze) {
    return maze_map_.GetCols();
  }
  return cave_map_.GetCols();
}

bool Loader::OpenFile(const QString& path) {
  bool is_loaded;
  if (type_ == GenerateType::kCave) {
    auto [ok, cave_map] = controller_->LoadCave(path.toStdString());
    cave_map_ = cave_map;
    is_loaded = ok;
  } else {
    auto [ok, maze_map] = controller_->LoadMaze(path.toStdString());
    maze_map_ = maze_map;
    is_loaded = ok;
  }
  if (is_loaded) {
    update();
  }
  return is_loaded;
}

bool Loader::SaveFile(const QString& path) {
  if (type_ == GenerateType::kCave) {
    return controller_->SaveCave(path.toStdString());
  }
  return controller_->SaveMaze(path.toStdString());
}

void Loader::GenerateMaze(size_t rows, size_t cols) {
  maze_solution_map_ = {};
  maze_map_ = controller_->GenerateMaze(rows, cols);
  update();
}

void Loader::GenerateCave(const cave::Params& params) {
  cave_map_ = controller_->GenerateCave(params);
  update();
}

void Loader::GenerateCaveNext(const cave::Params& params) {
  cave_map_ = controller_->GenerateNextCave(params);
  update();
}

void Loader::DrawCave() {
  if (!cave_map_.GetRows() || !cave_map_.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(this);
  auto [scale_row, scale_col] =
      util::GetScaledCell(height(), width(), cave_map_);
  for (size_t i = 0; i < cave_map_.GetRows(); ++i) {
    for (size_t j = 0; j < cave_map_.GetCols(); ++j) {
      if (cave_map_[i][j]) {
        painter.fillRect(j * scale_col, i * scale_row, scale_col, scale_row,
                         Qt::black);
      }
    }
  }
  painter.end();
}

void Loader::DrawMaze() {
  if (!maze_map_.GetRows() || !maze_map_.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(this);
  auto [scale_row, scale_col] =
      util::GetScaledCell(height(), width(), maze_map_);
  painter.fillRect(0, 0, scale_col * maze_map_.GetCols(), 2, Qt::black);
  painter.fillRect(0, 0, 2, scale_row * maze_map_.GetRows(), Qt::black);
  for (size_t i = 0; i < maze_map_.GetRows(); ++i) {
    for (size_t j = 0; j < maze_map_.GetCols(); ++j) {
      if (maze_map_[i][j].right_wall) {
        painter.fillRect((j + 1) * scale_col, i * scale_row, 2, scale_row + 2,
                         Qt::black);
      }
      if (maze_map_[i][j].bottom_wall) {
        painter.fillRect(j * scale_col, (i + 1) * scale_row, scale_col + 2, 2,
                         Qt::black);
      }
      if (maze_solution_map_.Empty()) {
        continue;
      }
      if (maze_solution_map_[i][j].visited) {
        maze::Vector path_vector = maze_solution_map_[i][j].vector;
        if (path_vector == maze::Vector::kUp) {
          painter.fillRect((j + 1) * scale_col - scale_col / 2,
                           i * scale_row - scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_vector == maze::Vector::kDown) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           i * scale_row + scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_vector == maze::Vector::kLeft) {
          painter.fillRect(j * scale_col - scale_col / 2,
                           i * scale_row + scale_row / 2, scale_col + 2, 2,
                           Qt::red);
        } else if (path_vector == maze::Vector::kRight) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           (i + 1) * scale_row - scale_row / 2, scale_col + 2,
                           2, Qt::red);
        }
      }
    }
  }
  painter.end();
}

void Loader::DrawEventMaze(int x, int y) {
  static int indices_count_ = 0;
  static Indices indices_[2] = {};

  auto [scaled_row, scaled_col] =
      util::GetScaledCell(height(), width(), maze_map_);
  indices_[indices_count_++] = {y / scaled_row, x / scaled_col};
  // solve on second cell pick
  if (indices_count_ == 2) {
    auto [solved, maze_map] = controller_->SolveMaze(indices_[0], indices_[1]);
    maze_solution_map_ = maze_map;
    if (!solved) {
      qDebug() << "Cannot solve the maze, please check the gen algo";
    }
    indices_count_ = 0;
    update();
  }
}

void Loader::DrawEventCave(int x, int y) {
  if (!cave_map_.GetCols() || !cave_map_.GetRows()) {
    return;
  }
  auto [scaled_row, scaled_col] =
      util::GetScaledCell(height(), width(), cave_map_);
  cave_map_[y / scaled_row][x / scaled_col] = true;
  update();
}

void Loader::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    int x = event->pos().x();
    int y = event->pos().y();
    if (type_ == GenerateType::kCave) {
      DrawEventCave(x, y);
    } else {
      DrawEventMaze(x, y);
    }
  }
}

void Loader::paintEvent(QPaintEvent*) {
  if (type_ == GenerateType::kCave) {
    DrawCave();
  } else {
    DrawMaze();
  }
}

}  // namespace mcg
