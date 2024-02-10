#include <QApplication>

#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  mcg::Model m;
  mcg::Controller c(&m);
  mcg::View v(&c);
  v.show();
  return a.exec();
}
