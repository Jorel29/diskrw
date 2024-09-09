
#include "../include/manager.h"
#include <iostream>
#include <unordered_map>

#define READ_BLOCK_LEN 1000

void ReaderWriterManager::read_file(std::string filename) {
  read_results content;
  ReadJob job;
  job.file_content = content;
  if (m_files.contains(filename)) {
    m_files_read.emplace(filename, job.file_content);
    job.file = &m_files[filename];
    pool.add_read_job(job);
  } else {
    // file does not exist
  }
};

void ReaderWriterManager::write_file(std::string filename, char mode,
                                     std::string content) {

  WriteJob job;
  job.content = content, job.mode = mode;
  if (m_files.contains(filename)) {
    job.file = &m_files[filename];
    pool.add_write_job(job);
  } else {
    m_files.emplace(filename, filename);
    job.file = &m_files[filename];
    pool.add_write_job(job);
  }
};

std::vector<std::string>
ReaderWriterManager::access_past_read(std::string filename) {
  if (m_files_read.contains(filename)) {
    return pool.get_read(filename);
  } else {
    std::vector<std::string> error = {"error"};
    return error;
  }
};
//
// Manager holds the threadpool, api to add and remove jobs, and stores a list
// of results from reads
// API
// readfile(filename) -> store read into a cache to pull from later
// writefile(filename, content)
// access_past_read(filename) -> return whole read result
// we have a main function here to determine that this is the top of the
// process hierarchy

void print(std::vector<std::string> lines) {
  for (std::string line : lines) {
    std::cout << line;
  }
};

int main(int argc, char *argv[]) {
  ReaderWriterManager manager;
  std::string filename;
  std::string content;
  std::vector<std::string> read_result;
  char mode;
  char action;
  while (!std::cin.fail()) {

    std::cin >> action;
    switch (action) {
    case 'w':
      std::cout << "specify file to write to:\n";
      std::cin >> filename;
      std::cout << "Now select mode \n";
      std::cin >> mode;
      std::cout << "Write content\n";
      std::cin >> content;
      manager.write_file(filename, mode, content);
    case 'r':
      std::cout << "specify file to read:\n";
      std::cin >> filename;
      manager.read_file(filename);
    case 'p':
      std::cout << "specify file to print:\n";
      std::cin >> filename;
      read_result = manager.access_past_read(filename);
      print(read_result);
    }
  }

  return 0;
}
