#pragma once

#include <iostream>
#include <simulator/geometry.hpp>
#include <simulator/mechanics.hpp>
#include <simulator/my_types.hpp>
#include <simulator/materials.hpp>

struct IParticle
{
	Position position {0.0, 0.0, 0.0};
	Velocity velocity {0.0, 0.0, 0.0};
	Force force {0.0, 0.0, 0.0};
	IMaterial* material;
	IGeometry* geometry;
	
	virtual Entity get_type() = 0;

	virtual double get_radius() = 0;
	
	template<class T*>
	void set_material(T* material)
	{
		this->material = material;
	}
	
	template<class T*>
	void set_geometry(T* g)
	{
		this->geometry = g;
	}
	
	double get_density()
	{
		return material->get_density();	
	}
	
	double get_mass()
	{
		return geometry->get_volume()*material->get_density();	
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
	
	SphericParticle(double x, double y, double z, double vx, double vy, double vz, double r, double rho = 1.0)
	{
		position = Position{x, y, z}; 
		velocity = Velocity {vx,vy,vz}; 
		geometry = new Sphere(r);
		material = new LinearMaterial(rho);
	}
	
	SphericParticle(Position p, Velocity v, double r, LinearMaterial m) 
	{
		position = p;
		velocity = v;
		geometry = new Sphere(r);
		material = &m;
	}
	
	~SphericParticle()
	{
		//delete material;
		//delete geometry;
	}
	
	Entity get_type() override
	{
		return Entity::SphericParticle;
	}
	
	double get_radius() override
	{
		return this->geometry->get_radius();
	}
};
