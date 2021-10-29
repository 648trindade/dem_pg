#include <catch.hpp>

#include <simulator/geometry.hpp>
#include <simulator/analitic_geometry.hpp>

using namespace geometric;

TEST_CASE("Test Triangle")
{
	Point p1{0.0, 0.0, 0.0};
	Point p2{2.0, 0.0, 0.0};
	Point p3{0.0, 1.0, 0.0};
	
	PlanarGeometry p{};
	p.points.push_back(p1);
	p.points.push_back(p2);
	p.points.at(0).print();
	p.points.at(1).print();
	
	Triangule t1 = Triangule(p1, p2, p3);
	t1.points.push_back(p3);
	t1.points.at(0).print();
	t1.points.at(1).print();
	t1.points.at(2).print();
	
	auto check_point_outside_triangle = [&](Point& p, double expected_distance) {
		REQUIRE(!point_inside_triangle(&p, &t1));
		REQUIRE(std::abs(distance(&t1, &p) - expected_distance) < 1e-8);
	};
	{
		Point p{3.0, 0.0, 0.0};
		check_point_outside_triangle(p, 1.0);
	}

	auto check_point_inside_triangle = [&](Point& p, double expected_distance) {
		REQUIRE(point_inside_triangle(&p, &t1));
		REQUIRE(std::abs(distance(&t1, &p) - expected_distance) < 1e-8);
	};
	{
		Point p{0.0, 0.9999, 0.0};
		check_point_inside_triangle(p, 0.0);
	}
	{
		Point p{1.9999, 0.0, 0.0};
		check_point_inside_triangle(p, 1.e-4);
	}
	{
		Point p{0.0, 0.0, 100.0};
		check_point_inside_triangle(p, 100.0);
	}
	{
		Point p{0.5, 0.5, 0.0};
		check_point_inside_triangle(p, 0.5);
	}
}
