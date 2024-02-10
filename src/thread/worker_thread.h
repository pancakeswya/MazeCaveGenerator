#ifndef MAZECAVEGENERATOR_MCG_THREAD_WORKER_THREAD_H_
#define MAZECAVEGENERATOR_MCG_THREAD_WORKER_THREAD_H_

#include <QThread>
#include <atomic>

namespace mcg {

class WorkerThread : public QThread {
  Q_OBJECT
 public:
  explicit WorkerThread(int delay);

 public slots:
  void FinishWork();

 private:
  std::atomic<bool> run_;
  int delay_;
  void run() override;
 signals:
  void WorkIsRunning();
};

}  // namespace mcg

#endif  // MAZECAVEGENERATOR_MCG_THREAD_WORKER_THREAD_H_
