#ifndef MAZECAVEGENERATOR_MCG_VIEW_MAINWINDOW_H_
#define MAZECAVEGENERATOR_MCG_VIEW_MAINWINDOW_H_

#include "controller/controller.h"

#include <QMainWindow>
#include <functional>

namespace mcg {

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(Controller* controller = nullptr, QWidget *parent = nullptr);
  ~View() override;

 private:
  void InitWidgets();
  void OnGenerateCave(std::function<void(const cave::Params&)> generate);

  Ui::View *ui_;
 private slots:
  void OnDrawModeCaveClicked();
  void OnAutoGenerationClicked();
  void OnOpenFileClicked();
  void OnSaveFileClicked();
  void OnGenerateMazeClicked();
  void OnGenerateCaveClicked();
  void OnGenerateCaveNextClicked();
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_VIEW_MAINWINDOW_H
