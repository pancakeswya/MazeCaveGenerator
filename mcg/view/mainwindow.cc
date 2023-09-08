#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "thread/worker_thread.h"
#include "base/settings.h"
#include "ui_mainwindow.h"

namespace mcg {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  InitWidgets();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::InitWidgets() {
  connect(ui_->pushButton_OpenMaze, SIGNAL(clicked()), this,
          SLOT(OnOpenFileClicked()));
  connect(ui_->pushButton_OpenCave, SIGNAL(clicked()), this,
          SLOT(OnOpenFileClicked()));
  connect(ui_->pushButton_SaveMaze, SIGNAL(clicked()), this,
          SLOT(OnSaveFileClicked()));
  connect(ui_->pushButton_SaveCave, SIGNAL(clicked()), this,
          SLOT(OnSaveFileClicked()));
  connect(ui_->pushButton_DrawModeCave, SIGNAL(clicked()), this,
          SLOT(OnDrawModeCaveClicked()));
  connect(ui_->pushButton_AutoGenCave, SIGNAL(clicked()), this,
          SLOT(OnAutoGenerationClicked()));
  connect(ui_->pushButton_GenerateCave, SIGNAL(clicked()), this,
          SLOT(OnGenerateCaveClicked()));
  connect(ui_->pushButton_GenerateMaze, SIGNAL(clicked()), this,
          SLOT(OnGenerateMazeClicked()));
  connect(ui_->horizontalSlider_MazeRows, &QSlider::valueChanged,
          ui_->spinBox_MazeRows, &QSpinBox::setValue);
  connect(ui_->spinBox_MazeRows, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontalSlider_MazeRows, &QSlider::setValue);
  connect(ui_->horizontalSlider_MazeCols, &QSlider::valueChanged,
          ui_->spinBox_MazeCols, &QSpinBox::setValue);
  connect(ui_->spinBox_MazeCols, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontalSlider_MazeCols, &QSlider::setValue);
  connect(ui_->horizontalSlider_CaveRows, &QSlider::valueChanged,
          ui_->spinBox_CaveRows, &QSpinBox::setValue);
  connect(ui_->spinBox_CaveRows, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontalSlider_CaveRows, &QSlider::setValue);
  connect(ui_->horizontalSlider_CaveCols, &QSlider::valueChanged,
          ui_->spinBox_CaveCols, &QSpinBox::setValue);
  connect(ui_->spinBox_CaveCols, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontalSlider_CaveCols, &QSlider::setValue);
  connect(ui_->tabWidget, &QTabWidget::currentChanged, ui_->McgLoader,
          &Loader::ChangeType);
  connect(ui_->pushButton_NextGenCave, &QPushButton::clicked, ui_->McgLoader,
          &Loader::NextGenCave);
  ui_->spinBox_delay->setRange(1, std::numeric_limits<int>::max());
  ui_->horizontalSlider_MazeRows->setRange(settings::kRowsMin, settings::kRowsMax);
  ui_->horizontalSlider_MazeCols->setRange(settings::kColsMin, settings::kColsMax);
  ui_->horizontalSlider_CaveRows->setRange(settings::kRowsMin, settings::kRowsMax);
  ui_->horizontalSlider_CaveCols->setRange(settings::kColsMin, settings::kColsMax);
  ui_->spinBox_LifeChance->setRange(settings::kLifeChanceMin, settings::kLifeChanceMax);
  ui_->spinBox_LiveLimitMin->setRange(settings::kLimitsMin, settings::kLimitsMax);
  ui_->spinBox_LiveLimitMax->setRange(settings::kLimitsMin, settings::kLimitsMax);
  ui_->spinBox_BornLimitMin->setRange(settings::kLimitsMin, settings::kLimitsMax);
  ui_->spinBox_BornLimitMax->setRange(settings::kLimitsMin, settings::kLimitsMax);
}

void MainWindow::OnOpenFileClicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
  if (!filepath.isEmpty()) {
    bool is_loaded = ui_->McgLoader->OpenFile(filepath);
    if (!is_loaded) {
      QMessageBox::warning(this, "Invalid file", "Invalid file or missing");
    }
  }
}

void MainWindow::OnSaveFileClicked() {
  QString filepath = QFileDialog::getSaveFileName(
      this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
  if (!filepath.isEmpty()) {
    bool is_saved = ui_->McgLoader->SaveFile(filepath);
    if (!is_saved) {
      QMessageBox::warning(this, "Invalid path", "Cannot save there");
    }
  }
}

void MainWindow::OnGenerateMazeClicked() {
  size_t rows = ui_->spinBox_MazeRows->value();
  size_t cols = ui_->spinBox_MazeCols->value();
  ui_->McgLoader->GenerateMaze(rows, cols);
}

void MainWindow::OnAutoGenerationClicked() {
  int delay = ui_->spinBox_delay->value();
  auto worker = new WorkerThread(delay);
  connect(worker, &WorkerThread::WorkIsRunning, ui_->McgLoader,
          &Loader::NextGenCave);
  connect(ui_->pushButton_StopAutoGen, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(worker, &WorkerThread::finished, worker, &WorkerThread::quit);
  connect(worker, &WorkerThread::finished, worker, &WorkerThread::deleteLater);
  worker->start();
}

void MainWindow::OnGenerateCaveClicked() {
  size_t rows = ui_->spinBox_CaveRows->value();
  size_t cols = ui_->spinBox_CaveCols->value();
  size_t life_chance = ui_->spinBox_LifeChance->value();
  Range born_limit = {ui_->spinBox_BornLimitMin->value(),
                      ui_->spinBox_BornLimitMax->value()};
  Range live_limit = {ui_->spinBox_LiveLimitMin->value(),
                      ui_->spinBox_LiveLimitMax->value()};
  ui_->McgLoader->GenerateCave(rows, cols, life_chance, born_limit, live_limit);
}

void MainWindow::OnDrawModeCaveClicked() {
  size_t rows = ui_->spinBox_CaveRows->value();
  size_t cols = ui_->spinBox_CaveCols->value();
  ui_->McgLoader->GenerateCave(rows, cols);
}

}  // namespace mcg
