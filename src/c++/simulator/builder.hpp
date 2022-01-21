#pragma once

#include "geometry.hpp"
#include "particle.hpp"

#include <memory>
#include <vector>

class Builder {
public:
    static std::vector<std::shared_ptr<SphericParticle>> create(
        const std::vector<Position>& positions,
        const std::vector<Velocity>& velocities,
        const std::vector<double>& radiuses
    );

};