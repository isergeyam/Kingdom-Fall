cmake_minimum_required(VERSION 3.8)
#set(HUNTER_ROOT, "cmake/hunter")
#include("cmake/HunterGate.cmake")
#include("cmake/cmake/Hunter")
#HunterGate(
    #URL "https://github.com/ruslo/hunter/archive/v0.19.52.tar.gz"
    #SHA1 "6d3a8135ba62726d810fd8c8c7d97980fa6c3b4a"
#)
project(game_proj)

set(CMAKE_CXX_STANDARD 11)
#hunter_add_package(nlohmann_json)
#find_package(nlohmann_json REQUIRED)
#include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(/home/linuxbrew/.linuxbrew/Cellar/nlohmann_json/3.1.0/include/)
set(SOURCE_FILES src/CObject.cpp src/CObject.hpp src/CPosition.cpp src/CPosition.hpp src/CUnit.cpp src/CUnit.hpp src/CField.cpp src/CField.hpp src/CUnitFactoryBuilder.cpp src/CUnitFactoryBuilder.hpp src/CUnitFactory.cpp src/CUnitFactory.hpp src/CGlobalSingleton.hpp src/CGlobalSingleton.cpp src/defines.hpp)
add_executable(game_proj ${SOURCE_FILES})