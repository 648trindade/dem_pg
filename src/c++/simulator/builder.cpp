#include "builder.hpp"

#include "analitic_geometry.hpp"
#include "boundaries.hpp"
#include "domain.hpp"
#include "integrator.hpp"
#include "interaction_forces.hpp"
#include "my_types.hpp"
#include "particle.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

std::vector<std::shared_ptr<SphericParticle>> ParticlesBuilder::create(
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

Domain DomainBuilder::create(size_t n_particles, Vector box_size, Point box_origin, double radius, double stiffness) {
    std::vector<Position> pos;
    std::vector<Velocity> vel;
    std::vector<double> radiis;

    size_t side = std::ceil(std::cbrt(n_particles));
    Vector delta = box_size / side;
    double max_diameter = std::min(std::min(delta.x, delta.y), delta.z);

    if (radius * 2 > max_diameter) {
        throw std::runtime_error(
            std::string("Too few space to put particles! ")
            + "diameter: " + std::to_string(radius * 2)
            + " max diameter: " + std::to_string(max_diameter)
        );
    }

    for (size_t i = 0; i < side; ++i) {
        for (size_t j = 0; j < side; ++j) {
            for (size_t k = 0; k < side; ++k) {
                Position position{
                    i * delta.x,
                    j * delta.y,
                    k * delta.z
                };

                pos.push_back(position + box_origin);
                vel.push_back(Velocity{0, 0, 0});
                radiis.push_back(radius);
            }
        }
    }

    auto particles_collection = ParticlesBuilder::create(pos, vel, radiis);

    ContactCollection contact_collection {};
    
    /* Setting interaction forces */
    InteractionForceCollection force_collection {};
    force_collection.add_interaction_force(std::make_shared<ContactForceCalculator>(stiffness));

    /* Creating Simulation domain */
    InteractionForceAssembler assembler(contact_collection, force_collection);
    Domain domain{particles_collection, assembler};

    return domain;
}
