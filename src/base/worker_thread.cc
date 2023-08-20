#include "worker_thread.h"

namespace mcg {

WorkerThread::WorkerThread(int delay) : delay_(delay), run_(false) {}

void WorkerThread::run() {
  run_ = true;
  while (run_) {
    emit WorkIsRunning();
    QThread::msleep(delay_);
  }
}

void WorkerThread::FinishWork() { run_ = false; }

}  // namespace mcg
