cmake_minimum_required(VERSION 3.29)
project(BoidSimulation2D)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(BoidSimulation2D main.cpp)

target_link_libraries(BoidSimulation2D PRIVATE SDL3::SDL3)
