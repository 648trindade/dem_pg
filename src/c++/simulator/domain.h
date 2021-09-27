#pragma once

#include <iostream>
#include <vector>

#include "particle.h"
#include "boundaries.h"
#include "interaction_forces.h"
#include "contact.h"


struct Domain
{
	private: 
		double _time {0.0};
	
	public :
		std::vector<std::shared_ptr<IParticle>>  particles;
		InteractionForceAssembler* interaction_force_assembler;
		std::vector<Boundary*> boundaries;
		Geometry* geometry;
	
		Domain () {};

		Domain(std::vector<std::shared_ptr<IParticle>> particles, InteractionForceAssembler& interaction_force_assembler) 
		: particles(particles), interaction_force_assembler(&interaction_force_assembler)
		{
		}

		Domain(InteractionForceAssembler& interaction_force_assembler) 
		{
			set_assembler(interaction_force_assembler);
		}
		
		template<class T>
		void add_particle(T& particle)
		{
			particles.push_back(std::make_shared<T>(particle));
		}
		
		void set_assembler(InteractionForceAssembler& interaction_force_assembler)
		{
			this->interaction_force_assembler = &interaction_force_assembler;
		}

		void set_geometry()
		{
		}
		
		void add_boundaries()
		{
		}
		
		double get_time() const
		{
			return _time;
		}
		
		void set_time(double t) 
		{
			_time = t;
		}
		
		void assemble_particle_forces()
		{
			for (auto particle_set : interaction_force_assembler->collection.particle_sets)
			{
				for (auto contact_force : interaction_force_assembler->interaction_forces_collection.interaction_forces)
				{
					contact_force->add_force(particle_set); 
				}
			}
		}
		
		void integrate(double delta_t)
		{
			for (auto particle : particles)
			{
				particle->move(delta_t);
			}

			_time += delta_t;

			std::cout <<"Current time = " << _time << std::endl;
		}
	
};
