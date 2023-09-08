#include "cave_painter.h"

#include <QPainter>
#include "util/util.h"

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

} // namespace mcg

