#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "threadsafefile.h"
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <unistd.h>
#include <unordered_map>
struct WriteJob {
  std::string content;
  char mode;
  ThreadSafeFile *file;
};

struct ReadJob {
  ThreadSafeFile *file;
  std::vector<std::string> file_content;
};
class ThreadPool {
public:
  void start();
  void add_write_job(WriteJob job);
  void add_read_job(ReadJob job);
  void stop();
  bool w_busy();
  bool r_busy();
  std::vector<std::string> get_read(std::string filename);

private:
  bool terminate = false;
  std::mutex r_mutex;
  std::mutex w_mutex;
  std::mutex c_mutex;
  std::condition_variable w_mutex_cv;
  std::condition_variable r_mutex_cv;
  std::vector<std::thread> w_threads;
  std::vector<std::thread> r_threads;
  std::queue<WriteJob> w_jobs;
  std::queue<ReadJob> r_jobs;
  std::unordered_map<std::string, std::vector<std::string>> reads_;
  void writer_thread() {
    WriteJob *job;
    while (true) {
      {
        std::unique_lock<std::mutex> lock(w_mutex);
        w_mutex_cv.wait(lock, [this] { return !w_jobs.empty() || terminate; });

        if (terminate)
          return;
        job = &w_jobs.front();
        ThreadSafeFile *writefile = job->file;
        writefile->write(job->content, job->mode);

        w_jobs.pop();
      }
    }
  };
  void reader_thread() {
    ReadJob *job;
    while (true) {
      {
        std::unique_lock<std::mutex> lock(r_mutex);
        r_mutex_cv.wait(lock, [this] { return !r_jobs.empty() || terminate; });
        if (terminate)
          return;

        job = &r_jobs.front();
        ThreadSafeFile *readfile = job->file;
        readfile->read(job->file_content);
        reads_.emplace(readfile->get_name(), job->file_content);
        r_jobs.pop();
      }
    }
  };
};

#endif // !THREADPOOL_H
