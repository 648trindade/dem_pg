#pragma once

#include "geometry.hpp"
#include "domain.hpp"
#include "particle.hpp"

#include <memory>
#include <vector>

class ParticlesBuilder {
public:
    static std::vector<std::shared_ptr<SphericParticle>> create(
        const std::vector<Position>& positions,
        const std::vector<Velocity>& velocities,
        const std::vector<double>& radiuses
    );

};

class DomainBuilder {
public:
    Domain create(
        size_t n_particles,
        Vector box_size = Vector{1, 1, 1},
        Position box_origin = Position{0, 0, 0},
        double radius = 1.0, 
        double stiffness = 1e-4
    );
};