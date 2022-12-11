cmake_minimum_required(VERSION 3.17.5)
project(Game)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

add_subdirectory(game)
add_subdirectory(KUDA)

