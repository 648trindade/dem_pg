#include <simulator/integrator.hpp>

void integrate(
    Domain &domain, double delta_t, double initial_time, double final_time,
    std::function<void(double, std::vector<std::shared_ptr<Entity>> const
                                   &)> const &callback) {
  domain.set_time(initial_time);

  while (domain.get_time() < final_time) {
    domain.interaction_force_assembler->search_contacts(domain.particles);
    domain.assemble_particle_forces();
    domain.integrate(delta_t);

    if (callback) {
      callback(domain.get_time(), domain.particles);
    }
  }
}
