cmake_minimum_required(VERSION 3.5)

set(SOURCES 
  src/main.cpp
  src/config/config.cpp
  src/file_tape/file_tape.cpp
  src/tape_sorter/tape_sorter.cpp
)

add_executable(tatlin ${SOURCES})

set_target_properties(
  tatlin PROPERTIES
  CXX_STANDART 20
  CXX_STANDART_REQUIRED ON
)

project(tatlin VERSION 0.0.1 LANGUAGES C CXX)
