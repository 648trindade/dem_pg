#include "builder.hpp"

#include <stdexcept>

std::vector<std::shared_ptr<SphericParticle>> Builder::create(
    const std::vector<Position>& positions,
    const std::vector<Velocity>& velocities,
    const std::vector<double>& radiuses
)
{
    std::vector<std::shared_ptr<SphericParticle>> collection;
    size_t num_particles = positions.size();

    if (positions.size() != velocities.size() || velocities.size() != radiuses.size())
    {
        throw std::runtime_error("Different number of property values");
    }

    collection.reserve(num_particles);

    for (size_t i = 0; i < num_particles; ++i)
    {
        collection.emplace_back(
            std::make_shared<SphericParticle>(
                positions[i], velocities[i], radiuses[i], new LinearMaterial(1)
            )
        );
    }

    return collection;
}