
#include <simulator/boundaries.hpp>

Point Boundary::get_point() const { return Point{0.0, 0.0, 0.0}; }

Vector Boundary::get_unitary_normal() const { return Vector{0.0, 0.0, 0.0}; }

EntityType Boundary::get_type() { return EntityType::Boundary; }

void Boundary::print() {}

double Boundary::get_radius() const { return -1.0; }

Wall::Wall(double x, double y, double z, double nx, double ny, double nz)
    : geometry(new InfinityPlane(x, y, z, nx, ny, nz)) {}

EntityType Wall::get_type() { return EntityType::Wall; }

void Wall::print() {
  geometry->point.print();
  geometry->normal.print();
}

Point Wall::get_point() const { return geometry->point; }

Vector Wall::get_unitary_normal() const {
  return geometry->get_unitary_normal();
}

InfinityHorizontalWall::InfinityHorizontalWall(double y)
    : Wall(0.0, y, 0.0, 0.0, 1.0, 0.0) {}

InfinityVerticalWall::InfinityVerticalWall(double x)
    : Wall(x, 0.0, 0.0, 1.0, 0.0, 0.0) {}
