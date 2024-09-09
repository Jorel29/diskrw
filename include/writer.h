#ifndef WRITER_H
#define WRITER_H
#include <fstream>
#include <string>

class Writer {

private:
  std::string m_filename;
  std::ofstream m_out;

public:
  Writer() = default;
  Writer(std::string filename);

  int write(std::string content, char mode);
};

#endif // !DISKRW_H
