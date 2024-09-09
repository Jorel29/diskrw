#ifndef MANAGER_H
#define MANAGER_H
#include "threadpool.h"
#include <string>
#include <unordered_map>
#include <vector>

#define READ_BLOCK_LEN 1000

class ReaderWriterManager {
  typedef std::vector<std::string> read_results;

private:
  ThreadPool pool;
  std::unordered_map<std::string, ThreadSafeFile> m_files;
  std::unordered_map<std::string, read_results> m_files_read;

public:
  ReaderWriterManager();

  void read_file(std::string filename);

  void write_file(std::string filename, char mode, std::string content);

  std::vector<std::string> access_past_read(std::string filename);
};

#endif // DEBUG
