#pragma once

#include <simulator/boundaries.hpp>
#include <simulator/geometry.hpp>
#include <simulator/my_types.hpp>
#include <simulator/particle.hpp>

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace geometric {
double distance(SphericParticle const &p1, SphericParticle const &p2);
double distance(SphericParticle const &p1, Wall const &b1);
// double distance(Boundary* b1, SphericParticle* p1);
double distance(Point const &p0, Point const &p1);
double distance(Edge const &e1, Point const &p1);
double distance(Triangule const &t1, Point const &p1);

double sign(Point *p1, Point *p2, Point *p3);
double sign(Point &p1, Point &p2, Point &p3);

bool point_inside_triangle(Point *p1, Triangule *t1);
} // namespace geometric

namespace Polymorphic {
double distance(Entity *p1, Entity *p2);
}
