#pragma once

#include <simulator/particle.hpp>

#include <vector>
#include <memory> 


struct ParticleSet
{
};

struct ContactPair : public ParticleSet
{
	std::vector<std::shared_ptr<IParticle>> particles;
	
	ContactPair(SphericParticle& i, SphericParticle& j) 
	{
		
		particles.push_back(std::make_shared<SphericParticle>(i));
		particles.push_back(std::make_shared<SphericParticle>(j));
	}

	ContactPair(SphericParticle* i, SphericParticle* j) 
	{
		particles.push_back(std::make_shared<SphericParticle>(*i));
		particles.push_back(std::make_shared<SphericParticle>(*j));
	}

	ContactPair(std::shared_ptr<SphericParticle> i, std::shared_ptr<SphericParticle> j) 
	{
		particles.push_back(i);
		particles.push_back(j);
	}
};

struct ContactBoundary : public ParticleSet
{
	std::vector<std::shared_ptr<IParticle>> particles;

	ContactBoundary(SphericParticle* p, Boundary* b)
	{
		particles.push_back(std::make_shared<SphericParticle>(*p));
		particles.push_back(std::make_shared<Boundary>(*b));
	}
	
	
	ContactBoundary(std::shared_ptr<SphericParticle> p, std::shared_ptr<Boundary> b)
	{
		particles.push_back(p);
		particles.push_back(b);
	}
};

struct ParticleCollection
{
	std::vector<std::shared_ptr<ParticleSet>> particle_sets;
	
	void add_contact_pair(ContactPair* pair)
	{
		particle_sets.push_back(std::make_shared<ContactPair>(*pair));
	}

	void add_contact_pair(std::shared_ptr<ContactPair> pair)
	{
		particle_sets.push_back(pair);
	}

	void add_contact_pair(ContactBoundary* pair)
	{
		particle_sets.push_back(std::make_shared<ContactBoundary>(*pair));
	}

	void add_contact_pair(std::shared_ptr<ContactBoundary> pair)
	{
		particle_sets.push_back(pair);
	}
};
