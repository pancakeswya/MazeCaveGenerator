#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->pushButton_OpenMaze, SIGNAL(clicked()), this, SLOT(OnOpenFileClicked()));
    connect(ui_->pushButton_OpenCave, SIGNAL(clicked()), this, SLOT(OnOpenFileClicked()));
    connect(ui_->pushButton_SaveMaze, SIGNAL(clicked()), this, SLOT(OnSaveFileClicked()));
    connect(ui_->pushButton_SaveCave, SIGNAL(clicked()), this, SLOT(OnSaveFileClicked()));
    connect(ui_->pushButton_GenerateMaze, SIGNAL(clicked()), this, SLOT(OnGenerateMazeClicked()));
    connect(ui_->horizontalSlider_Rows, &QSlider::valueChanged, ui_->spinBox_Rows, &QSpinBox::setValue);
    connect(ui_->spinBox_Rows, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_Rows, &QSlider::setValue);
    connect(ui_->horizontalSlider_Cols, &QSlider::valueChanged, ui_->spinBox_Cols, &QSpinBox::setValue);
    connect(ui_->spinBox_Cols, QOverload<int>::of(&QSpinBox::valueChanged), ui_->horizontalSlider_Cols, &QSlider::setValue);
    connect(ui_->tabWidget, &QTabWidget::currentChanged, ui_->LabyrinthLoader, &mcg::Loader::ChangeType);
    ui_->horizontalSlider_Rows->setRange(0, 50);
    ui_->horizontalSlider_Cols->setRange(0, 50);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::OnOpenFileClicked() {
    QString filepath = QFileDialog::getOpenFileName(
          this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
      if (!filepath.isEmpty()) {
          bool is_loaded = ui_->LabyrinthLoader->OpenFile(filepath);
          if (!is_loaded) {
              QMessageBox::warning(this, "Invalid file", "Invalid file or missing");
          }
      }
}

void MainWindow::OnSaveFileClicked() {
    QString filepath = QFileDialog::getSaveFileName(
          this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
    if (!filepath.isEmpty()) {
        bool is_saved = ui_->LabyrinthLoader->SaveFile(filepath);
        if (!is_saved) {
            QMessageBox::warning(this, "Invalid path", "Cannot save there");
        }
    }
}

void MainWindow::OnGenerateMazeClicked() {
    size_t rows = ui_->spinBox_Rows->value();
    size_t cols = ui_->spinBox_Cols->value();
    if (rows == 0 || cols == 0) {
        return;
    }
    ui_->LabyrinthLoader->GenerateMaze(rows, cols);
}

