#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <vector>
#include <memory> 
#include <cstring>

struct Point
{
	double x, y, z;
	
	Point() :
	x(0.0), y(0.0), z(0.0)
	{
	}
	
	Point(double x, double y, double z) :
	x(x), y(y), z(z)
	{
	}
	
	Point operator+(const Point& other)
	{
		return Point(x + other.x, y + other.y, z + other.z);
	}
	
	Point& operator+=(const Point& other)
	{
		this->x += other.x;
		this->y += other.y; 
		this->z += other.z;
		return *this;
	}
	
	Point& operator-=(const Point& other)
	{
		x += other.x;
		y += other.y; 
		z += other.z;
		return *this;
	}
	
	Point operator-(const Point& other) const
	{
		return Point(x - other.x, y - other.y, z - other.z);
	}
	
	Point operator*(const double& other)
	{
		return Point(x*other, y*other, z*other);
	}
	
	Point operator/(const double& other)
	{
		return Point(x/other, y/other, z/other);
	}
	
	bool operator==(const Point& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	
	Point& operator=(const Point& other)
	{
		if (this == &other) return *this;
		std::memcpy(this, &other, sizeof(Point));
		return *this;
	}
	
	
	double norm()
	{
		return std::sqrt((x)*(x) + (y)*(y) + (z)*(z));
	}
	
	double dot(const Point& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}
	
	Point cross(const Point& other) const
	{
		return Point(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x );
	}
	
	void print() const 
	{
		std::cout << "{ " << x << ", " << y << ", " << z << " }" <<std::endl;;
	}
};


using Vector = Point;


struct IGeometry
{
	virtual double get_radius() = 0;
	virtual double get_volume() = 0;
	virtual double get_surface() = 0; 
};

struct Geometry : public IGeometry
{
	double get_volume()  {return 0.0;}
	double get_surface()  {return 0.0;} 
	double get_radius()  {return 0.0;};
};

struct PrimitiveGeometry : public Geometry
{
	double get_volume()  {return 0.0;}
	double get_surface()  {return 0.0;}
	double get_radius() override {return 0.0;};
};

struct InfinityPlane : public PrimitiveGeometry 
{
	Point point;
	Vector normal;
	InfinityPlane(double x, double y, double z, double nx, double ny, double nz) :
	point(Point(x,y,z)),normal(Vector(nx,ny,nz))
	{}
	
	Vector get_unitary_normal()
	{
		return normal*(1.0/normal.norm());
	}
	
	double get_volume() override {return 0.0;}
	double get_surface() override {return 0.0;}
	 
};

struct Sphere : public PrimitiveGeometry 
{
	Point center;
	double radius;

	Sphere(double x, double y, double z, double radius) 
	{
		center = Point{x, y, z};
		this->radius = radius;
	}
	
	Sphere(double radius) : center(Point{0.0, 0.0, 0.0}), radius(radius)
	{
		Sphere(0.0, 0.0, 0.0, radius);
	}
	
	double get_volume() override {return get_surface()*radius/3.0;}
	double get_surface() override {return 4.0*M_PI*radius*radius;};
	double get_radius() override {return radius;};

};


struct Edge : public PrimitiveGeometry 
{
	static const int n_points {2};
	std::vector<Point> points;
	
	Edge(Point p1, Point p2)
	{
		points.push_back(p1);
		points.push_back(p2);
	}
	
	Vector get_vector()
	{
		return points.at(1) - points.at(0);
	}
	
	Vector get_unitary_direction()
	{
		Vector v = get_vector();
		return v/v.norm();
	}

	double get_volume() override {return 0.0;};
	double get_surface() override {return 0.0;};
	
};

struct PlanarGeometry : public PrimitiveGeometry 
{
	std::vector<Point> points;
	std::vector<Edge> edges;
	
	Vector get_normal()
	{
		return edges.at(0).get_vector().cross(edges.at(1).get_vector());
	}
	
	Vector get_unitary_normal()
	{
		Vector v = get_normal();
		return v/v.norm();
	}
	
	double get_volume() override {return 0.0;};
};

struct Square : public PlanarGeometry 
{
	static const int n_points {4};
	static const int n_edges {4};
	
	Square(Point p1, Point p2, Point p3, Point p4)
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
	
	double get_surface() override {return 0.0;};
};


struct Triangule : public PlanarGeometry 
{
	static const int n_points {3};
	static const int n_edges {3};
	std::vector<Point> points;
	
	Triangule(Point p1, Point p2, Point p3)
	{
		this->points.push_back(p1);
		this->points.push_back(p2);
		this->points.push_back(p3);
		
		this->edges.push_back(Edge(p2, p1));
		this->edges.push_back(Edge(p3, p2));
		this->edges.push_back(Edge(p3, p1));
		
	}

	double get_surface() override 
	{	
		Vector v1 = points.at(1) - points.at(0);
		Vector v2 = points.at(2) - points.at(0);
		Vector n = v2.cross(v1);
		return 0.5*n.norm();
	}
	
};
