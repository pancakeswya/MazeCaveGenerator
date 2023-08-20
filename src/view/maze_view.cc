#include "maze_view.h"

#include <QMouseEvent>
#include <QPainter>
#include <fstream>

#include "util.h"

namespace mcg {

bool MazeView::OpenFile(const QString &path) {
  maze_.Clear();
  std::ifstream file(path.toStdString().data(), std::ifstream::binary);
  if (!file.is_open()) {
    return false;
  }
  size_t rows, cols;
  file >> rows >> cols;
  maze_.SetRows(rows);
  maze_.SetCols(cols);
  for (auto &cell : maze_) {
    file >> cell.right_wall;
  }
  char c;
  do {
    file.get(c);
  } while (file.good() && c != '\n');
  for (auto &cell : maze_) {
    file >> cell.bottom_wall;
  }
  return true;
}

bool MazeView::SaveFile(const QString &path) {
  std::ofstream file(path.toStdString().data());
  if (!file) {
    return false;
  }
  file << maze_.GetRows() << ' ' << maze_.GetCols() << ' ' << '\n';
  SaveCells(
      maze_, [](const Cell &cell) { return cell.right_wall; }, file);
  file << '\n';
  SaveCells(
      maze_, [](const Cell &cell) { return cell.bottom_wall; }, file);
  file.close();
  return true;
}

inline ScaledSize MazeView::GetScaledCell(int w, int h) const noexcept {
  return {float(h) / maze_.GetRows(), float(w) / maze_.GetCols()};
}

inline bool MazeView::Solve(Indices curr, const Indices &target) {
  return maze_.Solve(std::move(curr), target);
}

bool MazeView::SolveOnMouseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    auto [scale_row, scale_col] = GetScaledCell(GetWidth(), GetHeight());
    indices_[indices_count_++] = {event->pos().y() / scale_row,
                                  event->pos().x() / scale_col};
    // solve on second click
    if (indices_count_ == 2) {
      Solve(indices_[0], indices_[1]);
      indices_count_ = 0;
      return true;
    }
  }
  return false;
}

void MazeView::Draw(QWidget *widget) {
  if (!maze_.GetRows() || !maze_.GetCols()) {
    return;
  }
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = GetScaledCell(GetWidth() - 2, GetHeight() - 2);
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

}  // namespace mcg