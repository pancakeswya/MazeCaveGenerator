#include "view/view.h"

#include <QFileDialog>
#include <QMessageBox>

#include "concurrency/worker_thread.h"
#include "base/constants.h"
#include "view/ui_view.h"

namespace mcg {

View::View(Controller* controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);
  InitWidgets();
  ui_->mcg_loader->SetController(controller);
}

View::~View() { delete ui_; }

void View::InitWidgets() {
  connect(ui_->pushbutton_open_maze, SIGNAL(clicked()), this,
          SLOT(OnOpenFileClicked()));
  connect(ui_->pushbutton_open_cave, SIGNAL(clicked()), this,
          SLOT(OnOpenFileClicked()));
  connect(ui_->pushbutton_save_maze, SIGNAL(clicked()), this,
          SLOT(OnSaveFileClicked()));
  connect(ui_->pushbutton_save_cave, SIGNAL(clicked()), this,
          SLOT(OnSaveFileClicked()));
  connect(ui_->pushbutton_draw_mode_cave, SIGNAL(clicked()), this,
          SLOT(OnDrawModeCaveClicked()));
  connect(ui_->pushbutton_autogen_cave, SIGNAL(clicked()), this,
          SLOT(OnAutoGenerationClicked()));
  connect(ui_->pushbutton_generate_cave, SIGNAL(clicked()), this,
          SLOT(OnGenerateCaveClicked()));
  connect(ui_->pushbutton_generate_maze, SIGNAL(clicked()), this,
          SLOT(OnGenerateMazeClicked()));
  connect(ui_->pushbutton_generate_cave_next, SIGNAL(clicked()), this,
          SLOT(OnGenerateCaveNextClicked()));
  connect(ui_->horizontal_slider_maze_rows, &QSlider::valueChanged,
          ui_->spinbox_maze_rows, &QSpinBox::setValue);
  connect(ui_->spinbox_maze_rows, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontal_slider_maze_rows, &QSlider::setValue);
  connect(ui_->horizontal_slider_maze_cols, &QSlider::valueChanged,
          ui_->spinbox_maze_cols, &QSpinBox::setValue);
  connect(ui_->spinbox_maze_cols, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontal_slider_maze_cols, &QSlider::setValue);
  connect(ui_->horizontal_slider_cave_rows, &QSlider::valueChanged,
          ui_->spinbox_cave_rows, &QSpinBox::setValue);
  connect(ui_->spinbox_cave_rows, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontal_slider_cave_rows, &QSlider::setValue);
  connect(ui_->horizontal_slider_cave_cols, &QSlider::valueChanged,
          ui_->spinbox_cave_cols, &QSpinBox::setValue);
  connect(ui_->spinbox_cave_cols, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->horizontal_slider_cave_cols, &QSlider::setValue);
  connect(ui_->tab_widget, &QTabWidget::currentChanged, ui_->mcg_loader,
          &Loader::SetType);
  ui_->spinbox_delay->setRange(1, std::numeric_limits<int>::max());
  ui_->horizontal_slider_maze_rows->setRange(constants::kRowsMin, constants::kRowsMax);
  ui_->horizontal_slider_maze_cols->setRange(constants::kColsMin, constants::kColsMax);
  ui_->horizontal_slider_cave_rows->setRange(constants::kRowsMin, constants::kRowsMax);
  ui_->horizontal_slider_cave_cols->setRange(constants::kColsMin, constants::kColsMax);
  ui_->spinbox_life_chance->setRange(constants::kLifeChanceMin, constants::kLifeChanceMax);
  ui_->spinbox_live_limit_min->setRange(constants::kLimitsMin, constants::kLimitsMax);
  ui_->spinbox_live_limit_max->setRange(constants::kLimitsMin, constants::kLimitsMax);
  ui_->spinbox_born_limit_min->setRange(constants::kLimitsMin, constants::kLimitsMax);
  ui_->spinbox_born_limit_max->setRange(constants::kLimitsMin, constants::kLimitsMax);
}

void View::OnOpenFileClicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
  if (!filepath.isEmpty()) {
    bool is_opened = ui_->mcg_loader->OpenFile(filepath);
    if (!is_opened) {
      QMessageBox::warning(this, "Invalid file", "Invalid file or missing");
    }
  }
}

void View::OnSaveFileClicked() {
  QString filepath = QFileDialog::getSaveFileName(
      this, tr("Open File"), QDir::homePath(), tr("Txt files (*.txt)"));
  if (!filepath.isEmpty()) {
    bool is_saved = ui_->mcg_loader->SaveFile(filepath);
    if (!is_saved) {
      QMessageBox::warning(this, "Invalid path", "Cannot save there");
    }
  }
}

void View::OnGenerateMazeClicked() {
  size_t rows = ui_->spinbox_maze_rows->value();
  size_t cols = ui_->spinbox_maze_cols->value();
  ui_->mcg_loader->GenerateMaze(rows, cols);
}

void View::OnAutoGenerationClicked() {
  int delay = ui_->spinbox_delay->value();
  auto worker = new WorkerThread(delay);
  connect(worker, SIGNAL(WorkIsRunning()), this, SLOT(OnGenerateCaveNextClicked()));
  connect(ui_->pushbutton_autogen_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_stop_autogen_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_generate_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_draw_mode_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_open_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_save_cave, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(ui_->pushbutton_generate_cave_next, &QPushButton::clicked, worker,
          &WorkerThread::FinishWork);
  connect(worker, &WorkerThread::finished, worker, &WorkerThread::quit);
  connect(worker, &WorkerThread::finished, worker, &WorkerThread::deleteLater);
  worker->start();
}

void View::OnDrawModeCaveClicked() {
  size_t rows = ui_->spinbox_cave_rows->value();
  size_t cols = ui_->spinbox_cave_cols->value();
  ui_->mcg_loader->GenerateCave({
    .rows = rows,
    .cols = cols
  });
}

inline void View::OnGenerateCave(std::function<void(const cave::Params&)> generate) {
    size_t rows = ui_->spinbox_cave_rows->value();
    size_t cols = ui_->spinbox_cave_cols->value();
    size_t life_chance = ui_->spinbox_life_chance->value();
    Range born_limit = {ui_->spinbox_born_limit_min->value(),
                        ui_->spinbox_born_limit_max->value()};
    Range live_limit = {ui_->spinbox_live_limit_min->value(),
                        ui_->spinbox_live_limit_max->value()};
    cave::Params params = {
        .rows = rows,
        .cols = cols,
        .life_chance = life_chance,
        .live_limit = live_limit,
        .born_limit = born_limit
    };
    generate(params);
}

void View::OnGenerateCaveClicked() {
    OnGenerateCave([&](const cave::Params& params) {
        ui_->mcg_loader->GenerateCave(params);
    });
}

void View::OnGenerateCaveNextClicked() {
    OnGenerateCave([&](const cave::Params& params) {
        ui_->mcg_loader->GenerateCaveNext(params);
    });
}

}  // namespace mcg
