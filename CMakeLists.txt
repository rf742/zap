cmake_minimum_required(VERSION 3.23.0)

project(ZAP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(./include)

set(COMMON_SOURCES point.cpp)
set(TARGET_SOURCES main.cpp)
set(TEST_SOURCES test_main.cpp test_point.cpp)
add_executable(zap ${COMMON_SOURCES} ${TARGET_SOURCES})
add_executable(test ${COMMON_SOURCES} ${TEST_SOURCES})

