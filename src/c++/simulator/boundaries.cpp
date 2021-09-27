
#include <simulator/boundaries.hpp>

Point Boundary::get_point()
{
	return Point{0.0, 0.0, 0.0};
}

Vector Boundary::get_unitary_normal()
{
	return Vector{0.0, 0.0, 0.0};
}

Entity Boundary::get_type()
{
	return Entity::Boundary;
}

void Boundary::print()
{
}

double Boundary::get_radius()
{
	return -1.0;
}

Wall::Wall(double x, double y, double z, double nx, double ny, double nz )
	: geometry(new InfinityPlane(x, y, z, nx, ny, nz))
{
}

Entity Wall::get_type()
{
	return Entity::Wall;
}

void Wall::print()
{
	geometry->point.print();
	geometry->normal.print();
}

Point Wall::get_point()
{
	return geometry->point;
}

Vector Wall::get_unitary_normal()
{
	return geometry->get_unitary_normal();
}

InfinityHorizontalWall::InfinityHorizontalWall(double y)
	: Wall(0.0, y, 0.0, 0.0, 1.0, 0.0)
{
}

InfinityVerticalWall::InfinityVerticalWall(double x)
	: Wall(x, 0.0, 0.0, 1.0, 0.0, 0.0)
{
}	
