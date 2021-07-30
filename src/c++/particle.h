#pragma once

#include <iostream>
#include "geometry.h"
#include "mechanics.h"
#include "my_types.h"
#include "materials.h"
struct IParticle
{
	Position position {0.0, 0.0, 0.0 };
	Velocity velocity {0.0, 0.0, 0.0 };
	Force force {0.0, 0.0, 0.0 };
	IMaterial* material;
	double _mass {1.0};
	
	IParticle() {};
	
	IParticle(double x, double y, double z, double vx, double vy, double vz) :
	position(x,y,z),velocity(vx,vy,vz),force(0.0, 0.0, 0.0), material(nullptr),_mass(1.0)
	{} 
	
	virtual Entity get_type()
	{
		return Entity::IParticle;
	}
	
	double get_mass()
	{
		return _mass;	
	}
	
	void add_force(const Force& force )
	{
		this->force += force;
	}
	
	void reset_force()
	{
		force.x = 0.0;
		force.y = 0.0;
		force.z = 0.0;
	}
	
	void move(double delta_t)
	{
		this->velocity += this->force*(delta_t/this->get_mass());
		this->position += this->velocity*delta_t;
		this->reset_force();
	}

	virtual double get_radius()
	{
		return 0.0;
	}
	
	void print_position() const 
	{
		std::cout << " {"<< position.x << ", " << position.y << ", " << position.z << "} ";	
	}

	void print_velocity() const 
	{
		std::cout << " {"<< velocity.x << ", " << velocity.y << ", " << velocity.z << "} ";	
	}
	
	void print_force() const 
	{
		std::cout << " {"<< this->force.x << ", " << this->force.y << ", " << this->force.z << "} ";	
	}
};


struct SphericParticle : public IParticle 
{
	double r {0.0}; 
	
	SphericParticle(double x, double y, double z, double vx, double vy, double vz, double r) :
	IParticle( x,y,z,vx,vy,vz),r(r) 
	{}
	
	Entity get_type() override
	{
		return Entity::SphericParticle;
	}

	double get_radius() override
	{
		return this->r;
	}
};
