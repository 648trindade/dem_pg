set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BASE_LIB_FILES
    simulator/analitic_geometry.cpp
    simulator/analitic_geometry.hpp
    simulator/boundaries.cpp
    simulator/boundaries.hpp
    simulator/contact.hpp
    simulator/domain.hpp
    simulator/geometry.hpp
    simulator/integrator.hpp
    simulator/interaction_forces.hpp
    simulator/materials.hpp
    simulator/mechanics.hpp
    simulator/my_types.hpp
    simulator/particle.hpp
)

add_library(
    dem_base
    STATIC
       ${BASE_LIB_FILES}
 )

add_executable(
    test_simulator
        simulator/test_dem_simulation.cpp
)
target_link_libraries(
    test_simulator
    dem_base
)

add_executable(
    test_geometry
        simulator/test_geometry.cpp
)
target_link_libraries(
    test_geometry
    dem_base
)
