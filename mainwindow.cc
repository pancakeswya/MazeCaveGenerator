#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    InitWidgets();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::InitWidgets() {
    connect(ui_->pushButton_OpenMaze, SIGNAL(clicked()), this, SLOT(OnOpenFileClicked()));
    connect(ui_->pushButton_OpenCave, SIGNAL(clicked()), this, SLOT(OnOpenFileClicked()));
    connect(ui_->pushButton_SaveMaze, SIGNAL(clicked()), this, SLOT(OnSaveFileClicked()));
    connect(ui_->pushButton_SaveCave, SIGNAL(clicked()), this, SLOT(OnSaveFileClicked()));
    connect(ui_->pushButton_DrawModeCave, SIGNAL(clicked()), this, SLOT(OnDrawModeCaveClicked()));
    connect(ui_->pushButton_AutoGenCave, SIGNAL(clicked()), this, SLOT(OnAutoGenerationClicked()));
    connect(ui_->pushButton_GenerateCave, SIGNAL(clicked()), this, SLOT(OnGenerateCaveClicked()));
    connect(ui_->pushButton_GenerateMaze, SIGNAL(clicked()), this, SLOT(OnGenerateMazeClicked()));
    connect(ui_->horizontalSlider_MazeRows, &QSlider::valueChanged, ui_->spinBox_MazeRows, &QSpinBox::setValue);
    connect(ui_->spinBox_MazeRows, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_MazeRows, &QSlider::setValue);
    connect(ui_->horizontalSlider_MazeCols, &QSlider::valueChanged, ui_->spinBox_MazeCols, &QSpinBox::setValue);
    connect(ui_->spinBox_MazeCols, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_MazeCols, &QSlider::setValue);
    connect(ui_->horizontalSlider_CaveRows, &QSlider::valueChanged, ui_->spinBox_CaveRows, &QSpinBox::setValue);
    connect(ui_->spinBox_CaveRows, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_CaveRows, &QSlider::setValue);
    connect(ui_->horizontalSlider_CaveCols, &QSlider::valueChanged, ui_->spinBox_CaveCols, &QSpinBox::setValue);
    connect(ui_->spinBox_CaveCols, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_CaveCols, &QSlider::setValue);
    connect(ui_->tabWidget, &QTabWidget::currentChanged, ui_->McgLoader, &mcg::Loader::ChangeType);
    connect(ui_->pushButton_NextGenCave, &QPushButton::clicked, ui_->McgLoader, &mcg::Loader::NextGenCave);
    ui_->horizontalSlider_MazeRows->setRange(0, 50);
    ui_->horizontalSlider_MazeCols->setRange(0, 50);
    ui_->horizontalSlider_CaveRows->setRange(0, 50);
    ui_->horizontalSlider_CaveCols->setRange(0, 50);
    ui_->spinBox_LifeChance->setRange(0,100);
    ui_->spinBox_LiveLimitMin->setRange(0,7);
    ui_->spinBox_LiveLimitMax->setRange(0,7);
    ui_->spinBox_BornLimitMin->setRange(0,7);
    ui_->spinBox_BornLimitMax->setRange(0,7);
    ui_->spinBox_delay->setRange(1, std::numeric_limits<int>::max());
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

void Worker::run() {
  run_ = true;
  while(run_) {
      emit WorkIsRunning();
      QThread::msleep(delay_);
  }
}

void Worker::FinishWork() {
  run_ = false;
}

void MainWindow::OnAutoGenerationClicked() {
   int delay = ui_->spinBox_delay->value();
   auto worker = new Worker(delay);
   connect(worker, &Worker::WorkIsRunning, ui_->McgLoader, &mcg::Loader::NextGenCave);
   connect(ui_->pushButton_StopAutoGen, &QPushButton::clicked, worker, &Worker::FinishWork);
   connect(worker, &Worker::finished, worker, &Worker::quit);
   connect(worker, &Worker::finished, worker, &Worker::deleteLater);
   worker->start();
}

void MainWindow::OnGenerateCaveClicked() {
    size_t rows = ui_->spinBox_CaveRows->value();
    size_t cols = ui_->spinBox_CaveCols->value();
    size_t life_chance = ui_->spinBox_LifeChance->value();
    mcg::Range born_limit = {ui_->spinBox_BornLimitMin->value(), ui_->spinBox_BornLimitMax->value()};
    mcg::Range live_limit = {ui_->spinBox_LiveLimitMin->value(), ui_->spinBox_LiveLimitMax->value()};
    ui_->McgLoader->GenerateCave(rows, cols, life_chance, born_limit, live_limit);
}

void MainWindow::OnDrawModeCaveClicked() {
    size_t rows = ui_->spinBox_CaveRows->value();
    size_t cols = ui_->spinBox_CaveCols->value();
    ui_->McgLoader->GenerateCave(rows, cols);
}

