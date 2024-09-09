cmake_minimum_required(VERSION 3.10)

project(Writer)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# coverage flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -coverage -O0")

add_executable(WriterTester 
  "writertest.cpp" 
  "../src/writer.cpp"
  "../src/reader.cpp"
  )

target_link_libraries(WriterTester gcov)

target_include_directories(WriterTester PRIVATE ../include)
target_compile_features(WriterTester PUBLIC cxx_std_23)
