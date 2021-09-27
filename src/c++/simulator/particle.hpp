#pragma once

#include <iostream>
#include <simulator/geometry.hpp>
#include <simulator/mechanics.hpp>
#include <simulator/my_types.hpp>
#include <simulator/materials.hpp>

struct IParticle
{
public:	
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
	
	double get_density();
	double get_mass();
	void add_force(const Force& force);
	void reset_force();
	void move(double delta_t);
	void print_position() const;
	void print_velocity() const;
	void print_force() const;

public:
	Position position {0.0, 0.0, 0.0};
	Velocity velocity {0.0, 0.0, 0.0};
	Force force {0.0, 0.0, 0.0};
	IMaterial* material;
	IGeometry* geometry;
};

struct SphericParticle : public IParticle 
{
	SphericParticle(
		double x,
		double y,
		double z,
		double vx,
		double vy,
		double vz,
		double r,
		double rho = 1.0
	);
	SphericParticle(Position p, Velocity v, double r, LinearMaterial m);
	~SphericParticle();
	Entity get_type() override;
	double get_radius() override;
};
