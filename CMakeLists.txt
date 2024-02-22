 cmake_minimum_required(VERSION 3.19)
 project(decimal)

 set(CMAKE_CXX_STANDARD 17)
 add_compile_options(-O2 -Wall)

 add_executable(main main.cpp)
 add_library(decimal STATIC decimal.cpp decimal.h)
 target_link_libraries(main decimal)
