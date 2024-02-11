#ifndef MAZECAVEGENERATOR_SRC_VIEW_LOADER_H
#define MAZECAVEGENERATOR_SRC_VIEW_LOADER_H

#include <QWidget>
#include <memory>
#include <utility>

#include "controller/controller.h"

namespace mcg {

enum GenerateType : bool { kCave = false, kMaze };

class Loader : public QWidget {
  Q_OBJECT

 public:
  explicit Loader(QWidget* parent = nullptr) noexcept;
  ~Loader() override = default;

  void SetController(Controller* controller) noexcept;

  bool OpenFile(const QString& path);
  bool SaveFile(const QString& path);

  size_t GetRows() const noexcept;
  size_t GetCols() const noexcept;

  void GenerateMaze(size_t rows, size_t cols);
  void GenerateCave(const cave::Params& params);

 public slots:
  void GenerateCaveNext(const cave::Params& params);
  void SetType(int);

 protected:
  void paintEvent(QPaintEvent*) override;
  void mousePressEvent(QMouseEvent*) override;

 private:
  void DrawCave();
  void DrawMaze();

  void DrawEventMaze(int x, int y);
  void DrawEventCave(int x, int y);

  bool type_;

  maze::WallsMap maze_map_;
  maze::SolutionMap maze_solution_map_;
  cave::WallsMap cave_map_;

  Controller* controller_;
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_VIEW_LOADER_H
