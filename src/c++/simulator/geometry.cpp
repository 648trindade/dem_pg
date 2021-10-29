#include <simulator/geometry.hpp>


Point::Point()
	: x(0.0)
	, y(0.0)
	, z(0.0)
{
}

Point::Point(double x, double y, double z)
	: x(x)
	, y(y)
	, z(z)
{
}

Point Point::operator+(const Point& other) const
{
	return Point(x + other.x, y + other.y, z + other.z);
}

Point& Point::operator+=(const Point& other)
{
	this->x += other.x;
	this->y += other.y; 
	this->z += other.z;
	return *this;
}

Point& Point::operator-=(const Point& other)
{
	x += other.x;
	y += other.y; 
	z += other.z;
	return *this;
}

Point Point::operator-(const Point& other) const
{
	return Point(x - other.x, y - other.y, z - other.z);
}

Point Point::operator*(const double& other) const
{
	return Point(x * other, y * other, z * other);
}

Point Point::operator/(const double& other) const
{
	return Point(x / other, y / other, z / other);
}

bool Point::operator==(const Point& other)
{
	return (x == other.x && y == other.y && z == other.z);
}

Point& Point::operator=(const Point& other)
{
	if (this == &other) return *this;
	std::memcpy(this, &other, sizeof(Point));
	return *this;
}

double Point::norm() const
{
	return std::sqrt((x)*(x) + (y)*(y) + (z)*(z));
}

double Point::dot(const Point& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Point Point::cross(const Point& other) const
{
	return Point(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x );
}

void Point::print() const 
{
	std::cout << "{ " << x << ", " << y << ", " << z << " }" <<std::endl;;
}

double Geometry::get_volume() const
{
	return 0.0;
}

double Geometry::get_surface() const
{
	return 0.0;
}

double Geometry::get_radius() const
{
	return 0.0;
}

double PrimitiveGeometry::get_volume() const
{
	return 0.0;
}

double PrimitiveGeometry::get_surface() const
{
	return 0.0;
}

double PrimitiveGeometry::get_radius() const
{
	return 0.0;
}

InfinityPlane::InfinityPlane(double x, double y, double z, double nx, double ny, double nz)
	: point(Point(x, y, z))
	, normal(Vector(nx, ny, nz))
{
}

Vector InfinityPlane::get_unitary_normal() const
{
	return normal * (1.0 / normal.norm());
}

double InfinityPlane::get_volume() const
{
	return 0.0;
}

double InfinityPlane::get_surface() const
{
	return 0.0;
}

Sphere::Sphere(double x, double y, double z, double radius)
	: center(Point{x, y, z})
	, radius(radius)
{
}

Sphere::Sphere(double radius)
	: center(Point{0.0, 0.0, 0.0})
	, radius(radius)
{
}

double Sphere::get_volume() const
{
	return get_surface() * radius / 3.0;
}

double Sphere::get_surface() const
{
	return 4.0 * M_PI * radius * radius;
}

double Sphere::get_radius() const
{
	return radius;
}

Edge::Edge(Point p1, Point p2)
{
	points.push_back(p1);
	points.push_back(p2);
}

Vector Edge::get_vector() const
{
	return points.at(1) - points.at(0);
}

Vector Edge::get_unitary_direction() const
{
	Vector v = get_vector();
	return v / v.norm();
}

double Edge::get_volume() const
{
	return 0.0;
}

double Edge::get_surface() const
{
	return 0.0;
}

Vector PlanarGeometry::get_normal() const
{
	return edges.at(0).get_vector().cross(edges.at(1).get_vector());
}

Vector PlanarGeometry::get_unitary_normal() const
{
	Vector v = get_normal();
	return v / v.norm();
}

double PlanarGeometry::get_volume() const
{
	return 0.0;
}

Square::Square(Point p1, Point p2, Point p3, Point p4)
{
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	
	edges.push_back(Edge(p2, p1));
	edges.push_back(Edge(p3, p2));
	edges.push_back(Edge(p4, p1));
	edges.push_back(Edge(p1, p2));
}

double Square::get_surface() const
{
	return 0.0;
}

Triangule::Triangule(Point p1, Point p2, Point p3)
{
	this->points.push_back(p1);
	this->points.push_back(p2);
	this->points.push_back(p3);
	
	this->edges.push_back(Edge(p2, p1));
	this->edges.push_back(Edge(p3, p2));
	this->edges.push_back(Edge(p3, p1));
}

double Triangule::get_surface() const
{	
	Vector v1 = points.at(1) - points.at(0);
	Vector v2 = points.at(2) - points.at(0);
	Vector n = v2.cross(v1);
	return 0.5*n.norm();
}
