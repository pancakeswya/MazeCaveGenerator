#ifndef MAZECAVEGENERATOR_SRC_VIEW_MAINWINDOW_H_
#define MAZECAVEGENERATOR_SRC_VIEW_MAINWINDOW_H_

#include <QMainWindow>

namespace mcg {

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private:
  void InitWidgets();
  Ui::MainWindow *ui_;
 private slots:
  void OnDrawModeCaveClicked();
  void OnAutoGenerationClicked();
  void OnOpenFileClicked();
  void OnSaveFileClicked();
  void OnGenerateMazeClicked();
  void OnGenerateCaveClicked();
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_VIEW_MAINWINDOW_H
