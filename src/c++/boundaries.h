﻿
#pragma once

#include <iostream>
#include "geometry.h"
#include "particle.h"
#include "my_types.h"

struct Boundary : public IParticle
{
	Geometry* geometry; 
	
	virtual Point get_point() {return Point{0.0, 0.0, 0.0};}
	virtual Vector get_unitary_normal() {return Vector{0.0, 0.0, 0.0};};
	
	Entity get_type() override {return Entity::Boundary;}
	
	virtual void print() {}
};


struct Wall : public Boundary
{
	InfinityPlane geometry;
	
	Wall(double x, double y, double z, double nx, double ny, double nz ) :
	geometry(InfinityPlane(x, y, z, nx, ny, nz))
	{
	}
	
	Entity get_type() override {return Entity::Wall;}
	
	void print() override
	{
		geometry.point.print();
		geometry.normal.print();
	}
	
	Point get_point() override
	{
		return geometry.point;
	};
	
	Vector get_unitary_normal() override
	{
		return geometry.get_unitary_normal();
	};
	
};

struct InfinityHorizontalWall : public Wall
{
	InfinityHorizontalWall(double y) :
	Wall(0.0, y, 0.0, 0.0, 1.0, 0.0)
	{}	
};

struct InfinityVerticalWall : public Wall
{
	InfinityVerticalWall(double x) :
	Wall(x, 0.0, 0.0, 1.0, 0.0, 0.0)
	{}	
};


	