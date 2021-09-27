#include <simulator/integrator.hpp>

void integrate(Domain& domain, double delta_t, double initial_time, double final_time)
{
	domain.set_time(initial_time);

	while (domain.get_time() < final_time) {
		domain.assemble_particle_forces();
		domain.integrate(delta_t);
	
		int count = 0;
		for (auto const& p : domain.particles) {
			std::cout << " Particle id = " << count;
			std::cout << ", Position = ";
			p->print_position();
			std::cout << ", Velocity = ";
			p->print_velocity();
			std::cout << "\n";
			count++;
		}
	}
}
