#include <simulator/domain.hpp>

Domain::Domain()
{
}

Domain::Domain(
	std::vector<std::shared_ptr<IParticle>> particles,
	InteractionForceAssembler& interaction_force_assembler) 
	: particles(particles)
	, interaction_force_assembler(&interaction_force_assembler)
{
}

Domain::Domain(InteractionForceAssembler& interaction_force_assembler) 
{
	set_assembler(interaction_force_assembler);
}

void Domain::set_assembler(InteractionForceAssembler& interaction_force_assembler)
{
	this->interaction_force_assembler = &interaction_force_assembler;
}

void Domain::set_geometry()
{
}

void Domain::add_boundaries()
{
}

double Domain::get_time() const
{
	return _time;
}

void Domain::set_time(double t) 
{
	_time = t;
}

void Domain::assemble_particle_forces()
{
	for (auto particle_set : interaction_force_assembler->collection.particle_sets) {
		for (auto contact_force : interaction_force_assembler->interaction_forces_collection.interaction_forces) {
			contact_force->add_force(particle_set); 
		}
	}
}

void Domain::integrate(double delta_t)
{
	for (auto particle : particles) {
		particle->move(delta_t);
	}

	_time += delta_t;
}
