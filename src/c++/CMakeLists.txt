set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    test_simulator
        simulator/test_dem_simulation.cpp
)

add_executable(
    test_geometry
        simulator/test_geometry.cpp
)
