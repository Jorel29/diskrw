#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/writer.h"
#include "../include/reader.h"
#include "doctest.h"

TEST_CASE("Write to file, mode o") {
  Writer testwriter = Writer("test.txt");
  int res = testwriter.write("testing writing a string\n", 'o');

  CHECK(res == 0);
}

TEST_CASE("write to file, mode a") {
  Writer testwriter = Writer("test.txt");
  int res = testwriter.write("adding content\n", 'a');

  CHECK(res == 0);
}

TEST_CASE("read file") {
  Reader testreader = Reader("readtest.txt", 1000);
  std::vector<std::string> content;
  int res = testreader.read_file();
  content = testreader.get_content();
  CHECK(content[0] == "hello");
  CHECK(res == 0);
}

TEST_CASE("read file multiline") {
  Reader testreader = Reader("readertestmulti.txt", 1000);
  std::vector<std::string> content;
  int res = testreader.read_file();
  content = testreader.get_content();
  CHECK(res == 0);
  CHECK(content[0] == "yo");
  CHECK(content[1] == "hello");
  CHECK(content[2] == "world");
}
