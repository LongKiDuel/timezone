cmake_minimum_required(VERSION 3.23.0)
project(abc VERSION 0.1.0)
   
include(CTest)
enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(reg regex.cpp)
add_executable(reg2 r2.cpp)
 
