#pragma once
#include <iostream>
#include <memory>

#include "particle.h"
#include "analitic_geometry.h"
#include "contact.h"


struct InteractionForce
{
	virtual void add_force(std::shared_ptr<ParticleSet> paticle_set) {};
};

struct ContactForce : public InteractionForce
{
	
	void add_force(std::shared_ptr<ParticleSet> paticle_set) 
	{
		ContactPair* contact_pair_ptr = reinterpret_cast<ContactPair*>(paticle_set.get());
		add_force(contact_pair_ptr);
	}; 

	void add_force(ContactPair* contact_set)
	{
		add_force(std::make_shared<ContactPair>(*contact_set));
	}
	
	void add_force(std::shared_ptr<ContactPair> contact_set)
	{
		
		auto& p1 = contact_set->particles.at(0) ;
		auto& p2 = contact_set->particles.at(1);
		double d = Polymorphic::distance(p1.get(), p2.get());

		if (d >= 0.0)
			return;
		
		Vector direction = p1->position - p2->position;
		Force force = direction*(stiffness/direction.norm());
		
		// action and reaction
		p2->add_force(force*-1.0);
		p1->add_force(force);
		  
	};

	static double stiffness;
};

double ContactForce::stiffness = 1.0E0;

struct InteractionForceCollection
{
	std::vector<std::shared_ptr<InteractionForce>> interaction_forces;
	
	void add_interaction_force(InteractionForce* interaction_force)
	{
		add_interaction_force(std::make_shared<InteractionForce>(*interaction_force));
	};

	void add_interaction_force(std::shared_ptr<InteractionForce> interaction_force)
	{
		interaction_forces.push_back(interaction_force);
	};

	void add_interaction_force(ContactForce* interaction_force)
	{
		add_interaction_force(std::make_shared<ContactForce>(*interaction_force));
	};

	void add_interaction_force(std::shared_ptr<ContactForce> interaction_force)
	{
		interaction_forces.push_back(interaction_force);
	};

};


struct InteractionForceAssembler
{
	ParticleCollection collection;
	InteractionForceCollection interaction_forces_collection;
	
	InteractionForceAssembler(){};
	
	InteractionForceAssembler(ParticleCollection& collection, InteractionForceCollection& interaction_forces_collection):
	collection(collection), interaction_forces_collection(interaction_forces_collection)
	{
	};
};

