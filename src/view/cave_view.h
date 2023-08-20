#ifndef MAZECAVEGENERATOR_SRC_VIEW_CAVE_VIEW_H_
#define MAZECAVEGENERATOR_SRC_VIEW_CAVE_VIEW_H_

#include "../model/cave.h"
#include "defs.h"
#include "view_interface.h"

namespace mcg {

class CaveView : public IView, public ViewSize {
 public:
  CaveView(int width, int height);
  bool OpenFile(const QString&) override;
  bool SaveFile(const QString&) override;
  bool SolveOnMouseEvent(QMouseEvent*) override;
  void Generate(size_t rows, size_t cols, size_t life_chance, const Range& live,
                const Range& born);
  void NextGeneration() noexcept;
  void Draw(QWidget*) override;

 private:
  [[nodiscard]] ScaledSize GetScaledCell() const noexcept;
  Cave cave_;
};

inline CaveView::CaveView(int width, int height) : ViewSize(width, height) {}

inline void CaveView::Generate(size_t rows, size_t cols, size_t life_chance,
                               const Range& live, const Range& born) {
  cave_.Generate(rows, cols, life_chance, live, born);
}

inline void CaveView::NextGeneration() noexcept { cave_.NextGeneration(); }

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_VIEW_CAVE_VIEW_H_
