
#pragma once

#include <simulator/geometry.hpp>
#include <simulator/particle.hpp>
#include <simulator/my_types.hpp>

#include <iostream>

struct Boundary : public IParticle
{
public:
	virtual Point get_point() const;
	virtual Vector get_unitary_normal() const;
	Entity get_type() override;
	double get_radius() const override;
	virtual void print();

public:
	Geometry* geometry; 
};

struct Wall : public Boundary
{
public:
	Wall(double x, double y, double z, double nx, double ny, double nz );
	Entity get_type() override;
	void print() override;
	Point get_point() const override;
	Vector get_unitary_normal() const override;

public:
	InfinityPlane* geometry;
};

struct InfinityHorizontalWall : public Wall
{
	InfinityHorizontalWall(double y);
};

struct InfinityVerticalWall : public Wall
{
	InfinityVerticalWall(double x);
};
