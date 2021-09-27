#include <iostream>

#include "geometry.h"
#include "analitic_geometry.h"

using namespace geometric;

#define fprint(x) std::cout << x << std::endl;


void test_triangule()
{
	Point p1 {0.0, 0.0, 0.0};
	Point p2 {2.0, 0.0, 0.0};
	Point p3 {0.0, 1.0, 0.0};
	
	PlanarGeometry p {};
	p.points.push_back(p1);
	p.points.push_back(p2);
	p.points.at(0).print();
	p.points.at(1).print();
	
	Triangule t1 = Triangule(p1, p2, p3);
	
	//Triangule t1 = Triangule().
	t1.points.push_back(p3);
	t1.points.at(0).print();
	t1.points.at(1).print();
	t1.points.at(2).print();
	
	double area = 1.0;
	double s = t1.get_surface();
	fprint("s = " << s);
	
	Vector n = t1.get_unitary_normal();
	n.print();
	
	Point p0 {0.0, 2.0, 0.0};
	bool is_inside = point_inside_triangle(&p0, &t1);
	fprint("p0 is inside = " << is_inside);
	double d = distance(&t1, &p0);
	fprint("d =  " << d );
	
	p0.x = 0.0;
	p0.y = 0.9999;
	
	is_inside = point_inside_triangle(&p0, &t1);
	fprint("p0 is inside = " << is_inside);
	d = distance(&t1, &p0);
	fprint("d =  " << d );
	
	p0.x = 1.99999;
	p0.y = 0.0;
	
	is_inside = point_inside_triangle(&p0, &t1);
	fprint("p0 is inside = " << is_inside);
	d = distance(&t1, &p0);
	fprint("d =  " << d );
	
	p0.x = 0.0;
	p0.y = 0.0;
	p0.z = 100.0;
	
	is_inside = point_inside_triangle(&p0, &t1);
	fprint("p0 is inside = " << is_inside);
	d = distance(&t1, &p0);
	fprint("d =  " << d );
	
	p0.x = 0.5;
	p0.y = 0.5;
	p0.z = 0.0;
	
	is_inside = point_inside_triangle(&p0, &t1);
	fprint("p0 is inside = " << is_inside);
	d = distance(&t1, &p0);
	fprint("d =  " << d );
		
}


int main()
{
	test_triangule();
	return 0;
}
