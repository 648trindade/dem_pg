set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BASE_LIB_FILES
    simulator/analitic_geometry.cpp
    simulator/analitic_geometry.hpp
    simulator/boundaries.cpp
    simulator/boundaries.hpp
    simulator/builder.cpp
    simulator/builder.hpp
    simulator/contact.cpp
    simulator/contact.hpp
    simulator/domain.cpp
    simulator/domain.hpp
    simulator/geometry.cpp
    simulator/geometry.hpp
    simulator/integrator.cpp
    simulator/integrator.hpp
    simulator/interaction_forces.cpp
    simulator/interaction_forces.hpp
    simulator/materials.cpp
    simulator/materials.hpp
    simulator/mechanics.hpp
    simulator/my_types.hpp
    simulator/particle.cpp
    simulator/particle.hpp
    io/simulator_io.hpp
    io/simulator_io.cpp
)

add_library(
    dem_base
    STATIC
       ${BASE_LIB_FILES}
)

add_library(
    test_main
    STATIC
       simulator/test_main.cpp
)

add_executable(
    test_simulator
        catch.hpp
        simulator/test_dem_simulation.cpp
)
target_link_libraries(
    test_simulator
        test_main
        dem_base
)

add_executable(
    test_builder
       catch.hpp
       simulator/test_builder.cpp
)
target_link_libraries(
    test_builder
        test_main
        dem_base
)

add_executable(
    test_geometry
        catch.hpp
        simulator/test_geometry.cpp
)
target_link_libraries(
    test_geometry
        test_main
        dem_base
)

add_test(
    NAME Builder
    COMMAND $<TARGET_FILE:test_builder>
)
add_test(
    NAME Geometry
    COMMAND $<TARGET_FILE:test_geometry>
)
add_test(
    NAME Simulator
    COMMAND $<TARGET_FILE:test_simulator>
)
