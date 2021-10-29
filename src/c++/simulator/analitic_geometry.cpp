#include <simulator/analitic_geometry.hpp>

namespace geometric
{
	double distance(SphericParticle const& p1, SphericParticle const& p2)
	{	
		Vector d = p1.get_position() - p2.get_position();
		// Important note: Negative distance means overlap
		return d.norm() - p1.get_radius() - p2.get_radius();
	}

	double distance(SphericParticle const& p1, Wall const& b1)
	{	
		Vector v = p1.get_position() - b1.get_point();
		Vector n = b1.get_unitary_normal();
		return v.dot(n) - p1.get_radius();
	}

	// double distance(Boundary* b1, SphericParticle* p1)
	// {    
	// 	return distance(p1, b1);
	// } 

	double distance(Point const& p0, Point const& p1)
	{
		return (p1 - p0).norm();
	}

	double distance(Edge const& e1, Point const& p1)
	{    
		Vector v = e1.get_vector();
		Point p0 = e1.points.at(0);
		Vector v1 = p1 - p0;
		double proj_length = v1.dot(v);

		if (proj_length <= 0.0) {
			return distance(p0, p1);
		} else if (proj_length >= v.norm()) {
			return distance(p1, e1.points.at(1));
		} else {
			Point p_closest = p0 + e1.get_unitary_direction() * proj_length;
			return distance(p1, p_closest);
		}
	}

	double distance(Triangule const& t1, Point const& p1)
	{
	    double l1 = distance(t1.edges.at(0), p1);
	    l1 = std::min(l1, distance(t1.edges.at(1), p1));
	    l1 = std::min(l1, distance(t1.edges.at(2), p1));
	    return l1;
	}

	double sign(Point* p1, Point* p2, Point* p3)
	{
    	return (p1->x - p3->x) * (p2->y - p3->y) - (p2->x - p3->x) * (p1->y - p3->y);
	}

	double sign(Point& p1, Point& p2, Point& p3)
	{
    	return sign (&p1, &p2, &p3);
	}

	bool point_inside_triangle(Point* p1, Triangule* t1)
	{
	    double d1, d2, d3;
	    bool has_neg, has_pos;

	    d1 = sign(*p1, t1->points.at(0), t1->points.at(1));
	    d2 = sign(*p1, t1->points.at(1), t1->points.at(2));
	    d3 = sign(*p1, t1->points.at(2), t1->points.at(0));

	    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	    return !(has_neg && has_pos);
	}
}

namespace Polymorphic 
{
	double distance(IParticle* p1, IParticle* p2)
	{	
		#define IS_SPHERIC(p) p->get_type() == Entity::SphericParticle
		#define IS_IPARTICLE(p) p->get_type() == Entity::SphericParticle
		#define IS_BOUNDARY(p) p->get_type() == Entity::Boundary
		#define IS_WALL(p) p->get_type() == Entity::Wall

		if (IS_SPHERIC(p1) && IS_SPHERIC(p2)) {
			return geometric::distance(*reinterpret_cast<SphericParticle*>(p1), *reinterpret_cast<SphericParticle*>(p2));
		}

		if (IS_SPHERIC(p1) && IS_WALL(p2)) {
			return geometric::distance(*reinterpret_cast<SphericParticle*>(p1), *reinterpret_cast<Wall*>(p2));
		}

		if (IS_WALL(p1) && IS_SPHERIC(p2)) {
			return geometric::distance(*reinterpret_cast<SphericParticle*>(p2), *reinterpret_cast<Wall*>(p1));
		}

		return 0.0;
	}
}
