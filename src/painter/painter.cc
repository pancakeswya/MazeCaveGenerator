#include "painter.h"
#include "util/util.h"

#include <QPainter>

namespace mcg {

void CavePainter::Draw(QWidget *widget) {
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = util::GetScaledCell(cave_);
  for (size_t i = 0; i < cave_.GetRows(); ++i) {
    for (size_t j = 0; j < cave_.GetCols(); ++j) {
      if (cave_[i][j] == 1) {
        painter.fillRect(j * scale_col, i * scale_row, scale_col, scale_row,
                         Qt::black);
      }
    }
  }
  painter.end();
}

void MazePainter::Draw(QWidget *widget) {
  if (!maze_.GetRows() || !maze_.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = util::GetScaledCell(maze_);
  painter.fillRect(0, 0, widget->width(), 2, Qt::black);
  painter.fillRect(0, 0, 2, widget->height(), Qt::black);
  for (size_t i = 0; i < maze_.GetRows(); ++i) {
    for (size_t j = 0; j < maze_.GetCols(); ++j) {
      if (maze_[i][j].right_wall) {
        painter.fillRect((j + 1) * scale_col, i * scale_row, 2, scale_row + 2,
                         Qt::black);
      }
      if (maze_[i][j].bottom_wall) {
        painter.fillRect(j * scale_col, (i + 1) * scale_row, scale_col + 2, 2,
                         Qt::black);
      }
      if (maze_[i][j].visited) {
        auto path_way = maze_[i][j].way;
        if (path_way == PathWay::kUp) {
          painter.fillRect((j + 1) * scale_col - scale_col / 2,
                           i * scale_row - scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_way == PathWay::kDown) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           i * scale_row + scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_way == PathWay::kLeft) {
          painter.fillRect(j * scale_col - scale_col / 2,
                           i * scale_row + scale_row / 2, scale_col + 2, 2,
                           Qt::red);
        } else if (path_way == PathWay::kRight) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           (i + 1) * scale_row - scale_row / 2, scale_col + 2,
                           2, Qt::red);
        }
      }
    }
  }
  painter.end();
}


} // namespace mcg
