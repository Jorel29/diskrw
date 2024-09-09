#ifndef THREAD_SAFE_FILE_H
#define THREAD_SAFE_FILE_H
#include "reader.h"
#include "writer.h"
#include <mutex>
#include <shared_mutex>

#define READ_BLOCK_LEN 1000

class ThreadSafeFile {
private:
  std::string filename_;
  std::shared_mutex mutex_;
  Reader reader_;
  Writer writer_;

public:
  ThreadSafeFile(std::string filename) {
    filename_ = filename;
    reader_ = Reader(filename, READ_BLOCK_LEN);
    writer_ = Writer(filename);
  };
  void write(std::string content, char mode) {
    std::unique_lock write_lock(mutex_);
    writer_.write(content, mode);
  };
  void read(std::vector<std::string> &content) {
    std::shared_lock read_lock(mutex_);
    reader_.read_file();
    content = reader_.get_content();
  }
  std::string get_name() { return filename_; }
};
#endif // !DEBUG
