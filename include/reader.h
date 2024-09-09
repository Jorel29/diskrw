#ifndef READER_H
#define READER_H

#include <fstream>
#include <string>
#include <vector>

class Reader {
private:
  std::string m_filename;
  std::ifstream m_in;
  std::vector<std::string> m_content;
  unsigned int m_max_block_len;

public:
  Reader() = default;
  Reader(std::string filename, unsigned int block_len);
  int read_file(); // reads entire file given a few
                   // assumtions: ends in '\n' and each
                   // line < MAX_CHAR_LEN 1000
  std::vector<std::string> get_content();
};

#endif // DEBUG
