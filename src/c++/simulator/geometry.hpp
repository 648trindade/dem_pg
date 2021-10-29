#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <vector>
#include <memory> 
#include <cstring>

struct Point
{
public:	
	Point();
	Point(double x, double y, double z);
	Point operator+(const Point& other);
	Point& operator+=(const Point& other);
	Point& operator-=(const Point& other);
	Point operator-(const Point& other) const;
	Point operator*(const double& other);
	Point operator/(const double& other);
	bool operator==(const Point& other);
	Point& operator=(const Point& other);
	double norm();
	double dot(const Point& other) const;
	Point cross(const Point& other) const;
	void print() const;

public:
	double x, y, z;
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
	double get_volume() override;
	double get_surface() override;
	double get_radius() override;
};

struct PrimitiveGeometry : public Geometry
{
	double get_volume() override;
	double get_surface() override;
	double get_radius() override;
};

struct InfinityPlane : public PrimitiveGeometry 
{
public:
	InfinityPlane(double x, double y, double z, double nx, double ny, double nz);
	Vector get_unitary_normal();
	double get_volume() override;
	double get_surface() override;

public:
	Point point;
	Vector normal;
};

struct Sphere : public PrimitiveGeometry 
{
public:
	Sphere(double x, double y, double z, double radius);
	Sphere(double radius);
	double get_volume() override;
	double get_surface() override;
	double get_radius() override;

public:
	Point center;
	double radius;
};

struct Edge : public PrimitiveGeometry 
{
public:
	Edge(Point p1, Point p2);
	Vector get_vector() const;
	Vector get_unitary_direction() const;
	double get_volume() override;
	double get_surface() override;

public:
	static const int n_points {2};
	std::vector<Point> points;
};

struct PlanarGeometry : public PrimitiveGeometry 
{
public:
	Vector get_normal();
	Vector get_unitary_normal();
	double get_volume() override;

public:
	std::vector<Point> points;
	std::vector<Edge> edges;
};

struct Square : public PlanarGeometry 
{
public:
	static constexpr int n_points = 4;
	static constexpr int n_edges = 4;

public:
	Square(Point p1, Point p2, Point p3, Point p4);
	double get_surface() override;
};

struct Triangule : public PlanarGeometry 
{
public:
	static constexpr int n_points = 3;
	static constexpr int n_edges = 3;

public:
	Triangule(Point p1, Point p2, Point p3);
	double get_surface() override;

public:
	std::vector<Point> points;
};
