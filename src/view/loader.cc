#include "view/loader.h"
#include "view/painter.h"
#include "base/util.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

namespace mcg {

Loader::Loader(QWidget *parent) noexcept : QWidget(parent), type_() {}

void Loader::SetController(Controller* controller) noexcept {
  controller_ = controller;
}

void Loader::SetType(int type) {
  type_ = type;
}

bool Loader::OpenFile(const QString& path) {
  bool is_loaded;
  if (type_ == GenerateType::kCave) {
    auto[ok, cave_map] = controller_->LoadCave(path.toStdString());
    cave_map_ = cave_map;
    is_loaded = ok;
  } else {
    auto[ok, maze_map] = controller_->LoadMaze(path.toStdString());
    maze_map_ = maze_map;
    is_loaded = ok;
  }
  if (is_loaded) {
    update();
  }
  return is_loaded;
}

bool Loader::SaveFile(const QString &path) {
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

void Loader::DrawEventMaze(int x, int y) {
  static int indices_count_ = 0;
  static Indices indices_[2] = {};

  auto [scaled_row, scaled_col] = util::GetScaledCell(maze_map_);
  indices_[indices_count_++] = {y / scaled_row, x / scaled_col};
  // solve on second cell pick
  if (indices_count_ == 2) {
    auto[solved, maze_map] = controller_->SolveMaze(indices_[0], indices_[1]);
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
  auto [scaled_row, scaled_col] = util::GetScaledCell(cave_map_);
  cave_map_[y / scaled_row][x / scaled_col] = true;
  update();
}

void Loader::mousePressEvent(QMouseEvent *event) {
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

void Loader::paintEvent(QPaintEvent *) {
  if (type_ == GenerateType::kCave) {
    cave::Draw(this, cave_map_);
  } else {
    maze::Draw(this, maze_map_, maze_solution_map_);
  }
}

}  // namespace mcg
