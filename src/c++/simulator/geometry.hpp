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
	Point operator+(const Point& other) const;
	Point& operator+=(const Point& other);
	Point& operator-=(const Point& other);
	Point operator-(const Point& other) const;
	Point operator*(const double& other) const;
	Point operator/(const double& other) const;
	bool operator==(const Point& other);
	Point& operator=(const Point& other);
	double norm() const;
	double dot(const Point& other) const;
	Point cross(const Point& other) const;
	void print() const;

public:
	double x, y, z;
};

using Vector = Point;

struct IGeometry
{
    virtual double get_radius() const = 0;
    virtual double get_volume() const = 0;
    virtual double get_surface() const = 0;
};

struct Geometry : public IGeometry
{
    double get_volume() const override;
    double get_surface() const override;
    double get_radius() const override;
};

struct PrimitiveGeometry : public Geometry
{
	double get_volume() const override;
	double get_surface() const override;
	double get_radius() const override;
};

struct InfinityPlane : public PrimitiveGeometry 
{
public:
	InfinityPlane(double x, double y, double z, double nx, double ny, double nz);
	Vector get_unitary_normal() const;
	double get_volume() const override;
	double get_surface() const override;

public:
	Point point;
	Vector normal;
};

struct Sphere : public PrimitiveGeometry 
{
public:
	Sphere(double x, double y, double z, double radius);
	Sphere(double radius);
	double get_volume() const override;
	double get_surface() const override;
	double get_radius() const override;

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
	double get_volume() const override;
	double get_surface() const override;

public:
	static const int n_points {2};
	std::vector<Point> points;
};

struct PlanarGeometry : public PrimitiveGeometry 
{
public:
    Vector get_normal() const;
    Vector get_unitary_normal() const;
	double get_volume() const override;
	Edge const& get_edge(int i) const;

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
	double get_surface() const override;
};

struct Triangule : public PlanarGeometry 
{
public:
	static constexpr int n_points = 3;
	static constexpr int n_edges = 3;

public:
	Triangule(Point p1, Point p2, Point p3);
	double get_surface() const override;

public:
	std::vector<Point> points;
};
