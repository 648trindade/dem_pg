project("DEM PlayGround" LANGUAGES CUDA CXX)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP REQUIRED)
find_package(CUDA REQUIRED)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 14)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

add_executable(
    dem_pg
    "src/c++/main.cpp"
    "src/c++/dgemm.h"
    "src/c++/dgemm.cu"
)
set_property(TARGET dem_pg PROPERTY CUDA_ARCHITECTURES 75)
set_property(TARGET dem_pg PROPERTY CXX_STANDARD 17)
target_link_libraries(dem_pg OpenMP::OpenMP_CXX)

install(
    TARGETS dem_pg
    RUNTIME DESTINATION "bin"
)