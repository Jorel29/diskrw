#include "../include/threadpool.h"
#include <shared_mutex>

void ThreadPool::start() {
  int max_threads = std::thread::hardware_concurrency();
  for (int i = 0; i < (max_threads / 2) - 1; i++) {
    w_threads.emplace_back(std::thread(&ThreadPool::writer_thread, this));
  }
  for (int i = 0; i < (max_threads / 2); i++) {
    r_threads.emplace_back(std::thread(&ThreadPool::reader_thread, this));
  }
};
void ThreadPool::add_write_job(WriteJob job) {
  {
    std::unique_lock<std::mutex> lock(w_mutex);
    w_jobs.push(job);
  }
  w_mutex_cv.notify_one();
};
void ThreadPool::add_read_job(ReadJob job) {
  {
    std::unique_lock<std::mutex> lock(r_mutex);
    r_jobs.push(job);
  }
  r_mutex_cv.notify_one();
};
void ThreadPool::stop() {
  {
    std::unique_lock<std::mutex> r_lock(r_mutex);
    std::unique_lock<std::mutex> w_lock(w_mutex);
    terminate = true;
  }
  r_mutex_cv.notify_all();
  w_mutex_cv.notify_all();
  for (std::thread &active_thread : w_threads) {
    active_thread.join();
  }
  for (std::thread &active_thread : r_threads) {
    active_thread.join();
  }
  w_threads.clear();
  r_threads.clear();
};
bool ThreadPool::w_busy() {
  bool w_busy;
  {
    std::unique_lock<std::mutex> lock(w_mutex);
    w_busy = !w_jobs.empty();
  }
  return w_busy;
};
bool ThreadPool::r_busy() {
  bool r_busy;
  {
    std::unique_lock<std::mutex> lock(r_mutex);
    r_busy = !r_jobs.empty();
  }
  return r_busy;
}
std::vector<std::string> ThreadPool::get_read(std::string filename) {
  std::vector<std::string> result = {"error"};

  {
    std::shared_lock<std::mutex> lock(r_mutex);
    if (reads_.contains(filename)) {
      result = reads_[filename];
    }
  }

  return result;
}
