#include "painter.h"

#include <QPainter>

#include "base/util.h"

namespace mcg {

namespace maze {

void Draw(QWidget* widget, const WallsMap& walls_map,
          const SolutionMap& solution_map) {
  if (!walls_map.GetRows() || !walls_map.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = util::GetScaledCell(walls_map);
  painter.fillRect(0, 0, widget->width(), 2, Qt::black);
  painter.fillRect(0, 0, 2, widget->height(), Qt::black);
  for (size_t i = 0; i < walls_map.GetRows(); ++i) {
    for (size_t j = 0; j < walls_map.GetCols(); ++j) {
      if (walls_map[i][j].right_wall) {
        painter.fillRect((j + 1) * scale_col, i * scale_row, 2, scale_row + 2,
                         Qt::black);
      }
      if (walls_map[i][j].bottom_wall) {
        painter.fillRect(j * scale_col, (i + 1) * scale_row, scale_col + 2, 2,
                         Qt::black);
      }
      if (solution_map.Empty()) {
        continue;
      }
      if (solution_map[i][j].visited) {
        Vector path_vector = solution_map[i][j].vector;
        if (path_vector == Vector::kUp) {
          painter.fillRect((j + 1) * scale_col - scale_col / 2,
                           i * scale_row - scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_vector == Vector::kDown) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           i * scale_row + scale_row / 2, 2, scale_row + 2,
                           Qt::red);
        } else if (path_vector == Vector::kLeft) {
          painter.fillRect(j * scale_col - scale_col / 2,
                           i * scale_row + scale_row / 2, scale_col + 2, 2,
                           Qt::red);
        } else if (path_vector == Vector::kRight) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           (i + 1) * scale_row - scale_row / 2, scale_col + 2,
                           2, Qt::red);
        }
      }
    }
  }
  painter.end();
}

}  // namespace maze

namespace cave {

void Draw(QWidget* widget, const WallsMap& walls_map) {
  if (!walls_map.GetRows() || !walls_map.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = util::GetScaledCell(walls_map);
  for (size_t i = 0; i < walls_map.GetRows(); ++i) {
    for (size_t j = 0; j < walls_map.GetCols(); ++j) {
      if (walls_map[i][j] == 1) {
        painter.fillRect(j * scale_col, i * scale_row, scale_col, scale_row,
                         Qt::black);
      }
    }
  }
  painter.end();
}

}  // namespace cave

}  // namespace mcg
