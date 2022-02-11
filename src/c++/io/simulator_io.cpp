#include "simulator/domain.hpp"
#include "simulator_io.hpp"

#include <string>
#include <fstream>

Base_IO::Base_IO(const Domain& domain): domain(domain) {}

csv_IO::csv_IO(const Domain& domain): Base_IO(domain){}

void csv_IO::Write() {

    const auto& particles = this->domain.get_particles();

    auto file = std::ofstream("particles_" + std::to_string(this->output_id) + ".csv");

    file << "radius,x,y,z,ux,uy,uz\n";
    for (auto const& particle : particles) {
        auto const& p = particle->position;
        auto const& v = particle->velocity;
        file << particle->get_radius() << ',';
        file << p.x << "," << p.y << "," << p.z << ",";
        file << v.x << "," << v.y << "," << v.z << '\n';
    }
    file.close();

    this->output_id++;
}