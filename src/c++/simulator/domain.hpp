#pragma once

#include <simulator/particle.hpp>
#include <simulator/boundaries.hpp>
#include <simulator/interaction_forces.hpp>
#include <simulator/contact.hpp>

#include <iostream>
#include <vector>

struct Domain
{	
public:
	Domain();
	Domain(
		std::vector<std::shared_ptr<IParticle>> particles,
		InteractionForceAssembler& interaction_force_assembler
	);
	Domain(InteractionForceAssembler& interaction_force_assembler);

	template<class T>
	void add_particle(T& particle)
	{
		particles.push_back(std::make_shared<T>(particle));
	}

	void set_assembler(InteractionForceAssembler& interaction_force_assembler);
	void set_geometry();
	void add_boundaries();
	double get_time() const;
	void set_time(double t);
	void assemble_particle_forces();
	void integrate(double delta_t);

public:
	std::vector<std::shared_ptr<IParticle>>  particles;
	InteractionForceAssembler* interaction_force_assembler;
	std::vector<Boundary*> boundaries;
	Geometry* geometry;

private:
	double _time {0.0};
};
