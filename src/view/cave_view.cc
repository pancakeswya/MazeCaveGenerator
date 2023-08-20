#include "cave_view.h"

#include <QMouseEvent>
#include <QPainter>
#include <fstream>

#include "util.h"

namespace mcg {

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
  SaveCells(
      cave_, [](int &cell) { return cell; }, file);
  return true;
}

inline ScaledSize CaveView::GetScaledCell() const noexcept {
  return {float(GetHeight()) / cave_.GetRows(),
          float(GetWidth()) / cave_.GetCols()};
}

bool CaveView::SolveOnMouseEvent(QMouseEvent *event) {
  if (!cave_.GetCols() || !cave_.GetRows()) {
    return false;
  }
  auto [scale_row, scale_col] = GetScaledCell();
  cave_.At(event->pos().y() / scale_row, event->pos().x() / scale_col) = 1;
  return true;
}

void CaveView::Draw(QWidget *widget) {
  QPainter painter;
  painter.begin(widget);
  auto [scale_row, scale_col] = GetScaledCell();
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

}  // namespace mcg