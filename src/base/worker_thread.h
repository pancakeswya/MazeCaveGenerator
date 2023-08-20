#ifndef MAZECAVEGENERATOR_SRC_BASE_WORKER_THREAD_H_
#define MAZECAVEGENERATOR_SRC_BASE_WORKER_THREAD_H_

#include <QThread>

namespace mcg {

class WorkerThread : public QThread {
  Q_OBJECT
 public:
  explicit WorkerThread(int delay);

 public slots:
  void FinishWork();

 private:
  volatile bool run_;
  int delay_;
  void run() override;
 signals:
  void WorkIsRunning();
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_SRC_BASE_WORKER_THREAD_H_
