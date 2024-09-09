#include "../include/reader.h"
#include <fstream>

Reader::Reader(std::string filename, unsigned int block_len) {
  m_filename = filename;
  m_max_block_len = block_len;
}

int Reader::read_file() {
  m_in.open(m_filename);

  char input_str[m_max_block_len];
  std::string linecontent;
  while (!m_in.eof()) {

    m_in.getline(input_str, m_max_block_len, '\n');
    linecontent = input_str;
    m_content.push_back(linecontent);
  }

  return 0;
}

std::vector<std::string> Reader::get_content() { return m_content; }
