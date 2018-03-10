cmake_minimum_required(VERSION 3.8)
project(game_proj)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/CObject.cpp src/CObject.h src/CPosition.cpp src/CPosition.h src/CUnit.cpp src/CUnit.hpp)
add_executable(game_proj ${SOURCE_FILES})