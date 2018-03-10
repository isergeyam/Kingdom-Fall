cmake_minimum_required(VERSION 3.8)
project(game_proj)

set(CMAKE_CXX_STANDARD 11)
include_directories(/home/linuxbrew/.linuxbrew/Cellar/nlohmann_json/3.1.0/include)
set(SOURCE_FILES src/CObject.cpp src/CObject.hpp src/CPosition.cpp src/CPosition.hpp src/CUnit.cpp src/CUnit.hpp src/CField.cpp src/CField.hpp src/CUnitAbstractFactory.cpp src/CUnitAbstractFactory.hpp)
add_executable(game_proj ${SOURCE_FILES})