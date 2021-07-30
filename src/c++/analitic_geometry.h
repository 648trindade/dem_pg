#pragma once

#include <iostream>

#include "boundaries.h"
#include "particle.h"
#include "my_types.h"


namespace geometric
{
	double distance(IParticle* p1, IParticle* p2)
	{	
		// TODO
		return 0.0;
	}
	 
	
	double distance(SphericParticle& p1, SphericParticle& p2)
	{	
		return distance(&p1, &p2);
	} 
	
	double distance(SphericParticle* p1, SphericParticle* p2)
	{	
		Vector d = p1->position - p2->position;
		return d.norm() -p1->get_radius() -p2->get_radius();
	} 
	
	double distance(IParticle* p1, Boundary* b1)
	{	
		// TODO
		return 0.0;
	} 
	
	
	double distance(SphericParticle* p1, Boundary* b1)
	{	
		// TODO
		return 0.0;
	} 
	
	
	double distance(SphericParticle* p1, Wall* b1)
	{	
		Vector v = p1->position - b1->get_point();
		Vector n = b1->get_unitary_normal();    
		return v.dot(n) - p1->get_radius(); 
	}
	
	double distance(Boundary* b1, SphericParticle* p1)
	{    
		return distance(p1, b1);
	} 
}


#define IS_SPHERIC(p) p->get_type() == Entity::SphericParticle
#define IS_IPARTICLE(p) p->get_type() == Entity::SphericParticle
#define IS_BOUNDARY(p) p->get_type() == Entity::Boundary
#define IS_WALL(p) p->get_type() == Entity::Wall

namespace Polymorphic 
{
	double distance(IParticle* p1, IParticle* p2)
	{	
		
		if ( IS_SPHERIC(p1) && IS_SPHERIC(p2))
			return geometric::distance(reinterpret_cast<SphericParticle*>(p1), reinterpret_cast<SphericParticle*>(p2));
		
		if ( IS_SPHERIC(p1) && IS_BOUNDARY(p2))
			return geometric::distance(reinterpret_cast<SphericParticle*>(p1), reinterpret_cast<Boundary*>(p2));
		
		if (IS_BOUNDARY(p1) && IS_SPHERIC(p2))
			return geometric::distance(reinterpret_cast<SphericParticle*>(p2), reinterpret_cast<Boundary*>(p1));
		
		if (IS_SPHERIC(p1) && IS_WALL(p2))
			return geometric::distance(reinterpret_cast<SphericParticle*>(p1), reinterpret_cast<Wall*>(p2));
		
		if (IS_WALL(p1) && IS_SPHERIC(p2))
			return geometric::distance(reinterpret_cast<SphericParticle*>(p2), reinterpret_cast<Wall*>(p1));
		
		return geometric::distance(p1, p2);
	}
}
