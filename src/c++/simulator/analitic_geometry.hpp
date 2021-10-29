#pragma once

#include <simulator/boundaries.hpp>
#include <simulator/particle.hpp>
#include <simulator/my_types.hpp>
#include <simulator/geometry.hpp>

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace geometric
{
    double distance(SphericParticle const& p1, SphericParticle const& p2);
    double distance(SphericParticle const& p1, Wall const& b1);
	// double distance(Boundary* b1, SphericParticle* p1);
	double distance(Point const& p0, Point const& p1);
	double distance(Edge const& e1, Point const& p1);

	double sign(Point* p1, Point* p2, Point* p3);
	double sign(Point& p1, Point& p2, Point& p3);

	bool point_inside_triangle(Point* p1, Triangule* t1);
	double distance(Triangule* t1, Point* p1);
}

namespace Polymorphic 
{
	double distance(IParticle* p1, IParticle* p2);
}
