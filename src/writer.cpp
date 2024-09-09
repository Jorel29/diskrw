#include "../include/writer.h"

Writer::Writer(std::string filename) { m_filename = filename; }

int Writer::write(std::string content, char mode) {
  switch (mode) {
  case 'a':
    m_out.open(m_filename, std::ios::app);
    break;
  case 'o':
    m_out.open(m_filename, std::ios::out);
    break;
  default:
    break;
  }

  const char *cstr_content = content.c_str();

  if (m_out.is_open()) {
    m_out.write(cstr_content, content.size());
  } else {
    return -1;
  }

  return 0;
}
