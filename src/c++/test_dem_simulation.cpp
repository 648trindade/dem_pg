

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "particle.h"
#include "boundaries.h"
#include "analitic_geometry.h"
#include "interaction_forces.h"
#include "domain.h"
#include "integrator.h"
#include "my_types.h"

using namespace geometric;

#define TEST_HEADER_START(test_name) std::cout << "\n" << std::string(30, '*') << "\n" \
<< test_name  << "\n" \
<< std::string(30, '*') << "\n" <<std::endl 

void test_types()
{
	TEST_HEADER_START("Test Entities Types");
	
	SphericParticle p1{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.1};
	
	bool is_sphere = p1.get_type() == Entity::SphericParticle;
	if (is_sphere)
		std::cout << "Particle is spheric" << std::endl;
	else
		std::cout << "Particle is not spheric" << std::endl;
}

void test_particle_and_walls_instances()
{
	TEST_HEADER_START("Test Entities Instances");

	SphericParticle p1{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.1};
	SphericParticle p2{1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	
	InfinityHorizontalWall w1{0.0};
	InfinityHorizontalWall w2{10.0};
	
	std::cout << "Walls" << std::endl;
	w1.print();
	w2.print();
		
	std::cout << "Particles" << std::endl;
	p1.print_position();
	p2.print_position();
	
	double d = distance(p1, p2);
	std::cout << "\nparticles distance = " << d << std::endl;
	
}


void test_spheric_particle_distance()
{
	TEST_HEADER_START("Test Particle Distance");

	SphericParticle* p1 = new SphericParticle(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.1);
	SphericParticle* p2 = new SphericParticle(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	
	std::vector<IParticle*> particles;
	particles.push_back(p1);
	particles.push_back(p2);

	for (auto p : particles)
	{
		Position position = p->position;
		double r = p->get_radius();
	}

	/* It is calling distance(IParticle* p1, IParticle* p2) */
	double d = distance(particles.at(0), particles.at(1));
}


void test_contact()
{
	TEST_HEADER_START("Test Contact");
	
	auto p1 = std::make_shared<SphericParticle>(SphericParticle{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.1});
	auto p2 = std::make_shared<SphericParticle>(SphericParticle{1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0});

	
	auto pair1 = std::make_shared<ContactPair>(ContactPair{p1, p2});
	
	ContactForce c {};
	c.add_force(pair1);
	
	std::cout << "\nparticles force = \n" << std::endl;
	
	for (auto p : pair1->particles)
	{
		p->print_position();
		p->print_force();
	}

	std::cout << "\n Move particles  \n" << std::endl;
	
	double delta_t {0.01};
	p1->move(delta_t);
	p2->move(delta_t);
	
	int i = 0;
	for (auto p : pair1->particles)
	{
		std::cout << " p " << i << std::endl;
		p->print_position();
		p->print_force();
		std::cout << " \n ";
		i++;
	}
		
	std::cout << "End Test Contact" << std::endl;
}

void test_two_particles_collision()
{

	TEST_HEADER_START("Test Particle Collision" );
	
	/* instantiating particles */
	auto p1 = std::make_shared<SphericParticle>(SphericParticle(1.0, 0.0, 0.0, 10.0, 0.0, 0.0, 1.0));
	auto p2 = std::make_shared<SphericParticle>(SphericParticle(3.1, 0.0, 0.0, -10.0, 0.0, 0.0, 1.0));

	std::vector<std::shared_ptr<IParticle>> particles;
	particles.push_back(p1);
	particles.push_back(p2);

	/* Creating contacts collections*/
	ContactPair pair {p1, p2};
	ParticleCollection collection;
	collection.add_contact_pair(std::make_shared<ContactPair>(pair));
	
	/* setting intertaction forces */
	ContactForce::stiffness = 1.0E5;
	ContactForce contact_force;	
	InteractionForceCollection int_force_collection;
	int_force_collection.add_interaction_force(std::make_shared<ContactForce>(contact_force));
	
 	/* Creating Simulation domain*/ 
 	InteractionForceAssembler assembler(collection, int_force_collection); 
 	Domain domain {particles, assembler};
	
 	for (auto p : domain.particles)
	{
		p->print_position();
		p->print_force();
	}
 	
 	/* Simulate*/
 	Integrator::integrate(domain, 0.001, 0.0, 0.01);

	std::cout << "End Collision" << std::endl;
}


void test_particles_wall_distance()
{

	TEST_HEADER_START( "Test Particle to Wall Distance");
	
	/* instantiating particles */
	SphericParticle* p1 = new SphericParticle(0.0, 1.0, 0.0, 10.0, 0.0, 0.0, 1.0);
	
	std::vector<IParticle*> particles;
	particles.push_back(p1);
	
	InfinityHorizontalWall* w1 = new InfinityHorizontalWall(-5.0);

	double d1 = distance(p1, w1);
	std::cout << "D = " << d1 << std::endl;
	
	/* Creating contacts collections*/
	ContactBoundary* pair = new ContactBoundary(p1, w1);
	double d2 = distance(pair->particles.at(0).get(), pair->particles.at(1).get());
	std::cout << "D = " << d1 << std::endl;
	
}

void test_particles_to_wall()
{

	TEST_HEADER_START( "Test Particle to Wall Collision");
	
	/* instantiating particles */
	auto p1 = std::make_shared<SphericParticle>(SphericParticle(0.0, 2.0, 0.0, 0.0, -100.0, 0.0, 1.0));
	
	std::vector<std::shared_ptr<IParticle>> particles;
	particles.push_back(p1);
	
	auto w1 = std::make_shared<InfinityHorizontalWall>(InfinityHorizontalWall(0.0));

	
	/* Creating contacts collections*/
	auto pair = std::make_shared<ContactBoundary>(ContactBoundary(p1, w1));

	ParticleCollection collection;
	collection.add_contact_pair(pair);
	
	/* setting intertaction forces */
	ContactForce::stiffness = 1.0E5;
	ContactForce contact_force;	
	InteractionForceCollection int_force_collection;
	int_force_collection.add_interaction_force(std::make_shared<ContactForce>(contact_force));
	
 	/* Creating Simulation domain*/
 	auto assembler = InteractionForceAssembler(collection, int_force_collection);
	Domain domain {particles, assembler };
 	//Domain domain {assembler};
	//domain.add_particle<SphericParticle>(*p1);
 	//domain.set_assembler(*assembler);
	
	/* Simulate*/
 	
 	Integrator::integrate(domain, 0.001, 0.0, 0.02);

	std::cout << "End Wall Collision" << std::endl;
 	
}


int main()
{
	std::cout << "DEM PG simulator" << std::endl;
	
	test_types();
	test_particle_and_walls_instances();
	test_spheric_particle_distance();
	test_contact();
	test_two_particles_collision();
	test_particles_wall_distance();
	test_particles_to_wall();
	
	return 0;
}

