cmake_minimum_required(VERSION 3.5)
project(Kingdom-Fall)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=leak -g -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
if (DEBUG STREQUAL "ON")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif ()
add_library(json-hpp INTERFACE)
target_include_directories(json-hpp
        INTERFACE
        third_party/nlohmann/)


add_subdirectory(third_party/json-schema-validator json-schema-validator)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(SOURCE_FILES src/CObject.cpp src/CObject.hpp src/CPosition.cpp src/CPosition.hpp src/CUnit.cpp src/CUnit.hpp src/CTerrain.cpp src/CTerrain.hpp src/CUnitFactoryBuilder.cpp src/CUnitFactoryBuilder.hpp src/defines.hpp src/json.hpp src/json-validator.hpp src/CObjectFactory.hpp src/CVillage.cpp src/CVillage.hpp src/CMapCell.cpp src/CMapCell.hpp src/CMap.cpp src/CMap.hpp src/CJsonSerializerAdapter.cpp src/CJsonSerializerAdapter.hpp src/CurrentSerializer.hpp src/CJsonValidatorAdapter.cpp src/CJsonValidatorAdapter.hpp src/CObjectFactoryValidateDecorator.hpp src/IObjectFactory.hpp src/CGlobalGame.cpp src/CGlobalGame.hpp)
if (WITH_TEST STREQUAL "ON")
    set(TEST_SOURCES ${SOURCE_FILES} test/test.hpp test/test.cpp)
    add_executable(MyTest ${TEST_SOURCES})
    target_include_directories(MyTest PUBLIC third_party)
    target_link_libraries(MyTest gtest)
    if (UNIX)
        target_link_libraries(MyTest pthread)
    endif ()
    target_link_libraries(MyTest json-schema-validator)
endif ()
