#include "loader.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <cmath>

namespace mcg {

Loader::Loader(QWidget *parent)
    : QWidget(parent), painter_(new CavePainter(cave_)), manager_(new CaveManager(cave_)) {}

void Loader::ChangeType(int type) {
  if (type) {
    painter_.reset(new MazePainter(maze_));
    manager_.reset(new MazeManager(maze_));
  } else {
    painter_.reset(new CavePainter(cave_));
    manager_.reset(new CaveManager(cave_));
  }
}

bool Loader::OpenFile(const QString &path) {
  bool is_loaded = manager_->Open(path.toStdString());
  if (is_loaded) {
    update();
  }
  return is_loaded;
}

bool Loader::SaveFile(const QString &path) { return manager_->Save(path.toStdString()); }

void Loader::GenerateMaze(size_t rows, size_t cols) {
  maze_.Generate(rows, cols);
  update();
}

void Loader::GenerateCave(size_t rows, size_t cols, size_t life_chance,
                          const Range &live, const Range &born) {
  cave_.Generate(rows, cols, life_chance, live, born);
  update();
}

void Loader::NextGenCave() {
  cave_.NextGeneration();
  update();
}

void Loader::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    bool event_is_ready =
        manager_->CustomCellEvent(event->pos().x(), event->pos().y());
    if (event_is_ready) {
      update();
    }
  }
}

void Loader::paintEvent(QPaintEvent *) { painter_->Draw(this); }

}  // namespace mcg
