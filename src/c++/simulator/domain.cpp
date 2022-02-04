#include <simulator/domain.hpp>

Domain::Domain() {}

Domain::Domain(InteractionForceAssembler &interaction_force_assembler) {
  set_assembler(interaction_force_assembler);
}

Domain::Domain(std::vector<std::shared_ptr<Particle>> const& particles,
               InteractionForceAssembler &interaction_force_assembler)
    : particles(particles),
      interaction_force_assembler(&interaction_force_assembler) {}

Domain::Domain(
      std::vector<std::shared_ptr<Particle>> const &particles,
      std::vector<std::shared_ptr<Boundary>> const &boundaries,
      InteractionForceAssembler &interaction_force_assembler)
      : particles(particles),
      boundaries(boundaries),
      interaction_force_assembler(&interaction_force_assembler) {}

void Domain::set_assembler(
    InteractionForceAssembler &interaction_force_assembler) {
  this->interaction_force_assembler = &interaction_force_assembler;
}

void Domain::set_geometry() {}

void Domain::add_boundary(std::shared_ptr<Boundary> boundary) {
    boundaries.push_back(boundary);
}

double Domain::get_time() const { return _time; }

void Domain::set_time(double t) { _time = t; }

void Domain::assemble_particle_forces() {
  for (auto particle_set :
       interaction_force_assembler->collection.particle_sets) {
    for (auto interaction_force :
         interaction_force_assembler->interaction_forces_collection
             .interaction_forces) {
      interaction_force->add_force(particle_set);
    }
  }
}

void Domain::integrate(double delta_t) {
  for (auto particle : particles) {
    particle->move(delta_t);
  }

  _time += delta_t;
}
