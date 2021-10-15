# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++abi")
set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_HOST_COMPILER "${CMAKE_CXX_COMPILER}")
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(VERBOSE 1)

project("DEM PlayGround" LANGUAGES CUDA CXX)
#project("DEM PlayGround" LANGUAGES CXX)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP REQUIRED)
find_package(CUDA REQUIRED)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} ${OpenMP_CXX_FLAGS}")

add_library(
   dem_pg_omp
       "src/c++/dgemm.h"
       "src/c++/dgemm.cpp"
)

target_link_libraries(
   dem_pg_omp
       OpenMP::OpenMP_CXX
)

if (CUDA17)
    cuda_add_library(
        dem_pg_cuda
            "src/c++/dgemm.h"
            "src/c++/dgemm.cu"
    )

    set_property(TARGET dem_pg_cuda PROPERTY CUDA_ARCHITECTURES 63)
    set_property(TARGET dem_pg_cuda PROPERTY CXX_STANDARD 17)

    add_executable(
        dem_pg
        "src/c++/main.cpp"
    )

    target_link_libraries(dem_pg dem_pg_omp)
    target_link_libraries(dem_pg dem_pg_cuda)

    install(
        TARGETS dem_pg
        RUNTIME DESTINATION "bin"
    )
endif (CUDA17)

include(CTest)
enable_testing()

add_subdirectory(src/c++)
