#pragma once

#include <simulator/particle.hpp>
#include <simulator/analitic_geometry.hpp>
#include <simulator/contact.hpp>

#include <iostream>
#include <memory>

struct InteractionForce
{
	virtual void add_force(std::shared_ptr<ParticleSet> paticle_set);
};

struct ContactForce : public InteractionForce
{
public:
    ContactForce(double stiffness);

	void add_force(std::shared_ptr<ParticleSet> paticle_set);
	void add_force(ContactPair* contact_set);
	void add_force(std::shared_ptr<ContactPair> contact_set);

private:
	double stiffness = 1.0;
};

struct InteractionForceCollection
{
public:	
	void add_interaction_force(InteractionForce* interaction_force);
	void add_interaction_force(std::shared_ptr<InteractionForce> interaction_force);
	void add_interaction_force(ContactForce* interaction_force);
	void add_interaction_force(std::shared_ptr<ContactForce> interaction_force);

public:
	std::vector<std::shared_ptr<InteractionForce>> interaction_forces;
};

struct InteractionForceAssembler
{
public:
	InteractionForceAssembler();
	InteractionForceAssembler(
		ParticleCollection& collection,
		InteractionForceCollection& interaction_forces_collection
	);

public:
	ParticleCollection collection;
	InteractionForceCollection interaction_forces_collection;
};
