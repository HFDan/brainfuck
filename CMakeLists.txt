CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(brainfuck "CXX")
set(CMAKE_CXX_STANDARD 20)

file(WRITE ${CMAKE_BINARY_DIR}/.gitignore "*")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(brainfuck ${CMAKE_SOURCE_DIR}/src/main.cpp)
