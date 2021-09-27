cmake_minimum_required(VERSION 3.1)

project(fdem)

set(CMAKE_CXX_STANDARD 17)
add_executable(test_simulator test_dem_simulation.cpp)
add_executable(test_geometry test_geometry.cpp)