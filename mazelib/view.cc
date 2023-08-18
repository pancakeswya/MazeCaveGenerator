#include "view.h"

#include <functional>
#include <fstream>
#include <QPainter>
#include <QMouseEvent>

namespace mcg {

namespace {

template<typename Tp, typename func>
void SaveCells(Matrix<Tp> &mcg, func GetCell, std::ofstream &os) {
  for (size_t i = 0; i < mcg.GetRows(); ++i) {
    for (size_t j = 0; j < mcg.GetCols(); ++j) {
      os << GetCell(mcg[i][j]);
      if (j != mcg.GetCols() - 1) {
        os << ' ';
      }
    }
    os << '\n';
  }
}

} // namespace

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
  SaveCells(maze_, [](const Cell &cell) {
    return cell.right_wall;
  }, file);
  file << '\n';
  SaveCells(maze_, [](const Cell &cell) {
    return cell.bottom_wall;
  }, file);
  file.close();
  return true;
}

inline bool MazeView::Solve(Indices curr, const Indices &target) {
  return maze_.Solve(std::move(curr), target);
}

bool MazeView::SolveOnMouseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    auto scale_row = float(GetHeight()) / maze_.GetRows();
    auto scale_col = float(GetWidth()) / maze_.GetCols();
    indices_[indices_count_++] = {event->pos().y() / scale_row, event->pos().x() / scale_col};
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
  auto scale_row = float(GetHeight() - 2) / maze_.GetRows();
  auto scale_col = float(GetWidth() - 2) / maze_.GetCols();
  painter.fillRect(0, 0, widget->width(), 2, Qt::black);
  painter.fillRect(0, 0, 2, widget->height(), Qt::black);
  for (size_t i = 0; i < maze_.GetRows(); ++i) {
    for (size_t j = 0; j < maze_.GetCols(); ++j) {
      if (maze_[i][j].right_wall) {
        painter.fillRect((j + 1) * scale_col, i * scale_row, 2, scale_row + 2, Qt::black);
      }
      if (maze_[i][j].bottom_wall) {
        painter.fillRect(j * scale_col, (i + 1) * scale_row, scale_col + 2, 2, Qt::black);
      }
      if (maze_[i][j].visited) {
        auto path_way = maze_[i][j].way;
        if (path_way == PathWay::kUp) {
          painter.fillRect((j + 1) * scale_col - scale_col / 2,
                           i * scale_row - scale_row / 2,
                           2,
                           scale_row + 2,
                           Qt::yellow);
        } else if (path_way == PathWay::kDown) {
          painter.fillRect(j * scale_col + scale_col / 2, i * scale_row + scale_row / 2, 2, scale_row + 2, Qt::yellow);
        } else if (path_way == PathWay::kLeft) {
          painter.fillRect(j * scale_col - scale_col / 2, i * scale_row + scale_row / 2, scale_col + 2, 2, Qt::yellow);
        } else if (path_way == PathWay::kRight) {
          painter.fillRect(j * scale_col + scale_col / 2,
                           (i + 1) * scale_row - scale_row / 2,
                           scale_col + 2,
                           2,
                           Qt::yellow);
        }
      }
    }
  }
  painter.end();
}

bool CaveView::OpenFile(const QString &path) {
  std::ifstream file(path.toStdString().data(), std::ifstream::binary);
  if (!file.is_open()) {
    return false;
  }
  size_t rows, cols;
  file >> rows >> cols;
  cave_.SetRows(rows);
  cave_.SetCols(cols);
  for (auto &cell : cave_) {
    file >> cell;
  }
  return true;
}

bool CaveView::SaveFile(const QString &path) {
  std::ofstream file(path.toStdString().data());
  if (!file) {
    return false;
  }
  file << cave_.GetRows() << ' ' << cave_.GetCols() << ' ' << '\n';
  SaveCells(cave_, [](int &cell) {
    return cell;
  }, file);
  return true;
}

bool CaveView::SolveOnMouseEvent(QMouseEvent *) {
  return false;
}

void CaveView::Draw(QWidget *widget) {
  QPainter painter;
  painter.begin(widget);
  auto scale_row = float(GetHeight()) / cave_.GetRows();
  auto scale_col = float(GetWidth()) / cave_.GetCols();
  for (size_t i = 0; i < cave_.GetRows(); ++i) {
    for (size_t j = 0; j < cave_.GetCols(); ++j) {
      if (cave_[i][j] == 1) {
        painter.fillRect(j * scale_col, i * scale_row, scale_col, scale_row, Qt::black);
      }
    }
  }
  painter.end();
}

} // namespace mcg
