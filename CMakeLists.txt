set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(VERBOSE 1)

project("DEM PlayGround" LANGUAGES CXX)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(src/c++)
