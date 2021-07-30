#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <vector>

struct Point
{
	double x,y,z;
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
	virtual double get_volume() = 0;
	virtual double get_surface() = 0; 
};

struct Geometry : public IGeometry
{
	double get_volume()  {return 0.0;}
	double get_surface()  {return 0.0;} 
};

struct PrimitiveGeometry : public Geometry
{
	double get_volume()  {return 0.0;}
	double get_surface()  {return 0.0;}
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

	Sphere(double x, double y, double z, double radius) : center(Point{x, y, z}), radius(radius)
	{}
	
	double get_volume() override {return get_surface()*radius/3.0;}
	double get_surface() override {return 4.0*M_PI*radius*radius;};

};


struct Edge : public PrimitiveGeometry 
{
	inline static int n_points {2};
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
	
	double get_volume() override {return 0.0;};
};

struct Square : public PlanarGeometry 
{
	inline static const int n_points {4};
	inline static const int n_edges {4};
	
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
	inline static const int n_points {3};
	inline static const int n_edges {3};
	
	Triangule(Point p1, Point p2, Point p3)
	{
		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);
		
		edges.push_back(Edge(p2, p1));
		edges.push_back(Edge(p3, p2));
		edges.push_back(Edge(p3, p1));
		
	}
	
	double get_surface() override {return 0.0;};
};
