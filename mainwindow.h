#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

class Worker : public QThread {
  Q_OBJECT
 public:
  explicit Worker(int delay) : delay_(delay), run_(false) {}

public slots:
  void FinishWork();
 private:
  volatile bool run_;
  int delay_;
  void run() override;
 signals:
  void WorkIsRunning();
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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
#endif // MAINWINDOW_H
