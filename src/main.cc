#include <QApplication>

#include "controller/controller.h"
#include "model/cave_model.h"
#include "model/maze_model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  mcg::MazeModel maze_m;
  mcg::CaveModel cave_m;
  mcg::Controller c(&maze_m, &cave_m);
  mcg::View v(&c);
  v.show();
  return a.exec();
}
