#include <simulator/particle.hpp>
#include <simulator/boundaries.hpp>
#include <simulator/analitic_geometry.hpp>
#include <simulator/interaction_forces.hpp>
#include <simulator/domain.hpp>
#include <simulator/integrator.hpp>
#include <simulator/my_types.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <assert.h>  

using namespace geometric;

#define LINE_SEPARATOR std::cout << "\n" << std::string(30, '*') << "\n"

#define TEST_HEADER_START(test_name)  LINE_SEPARATOR \
<< test_name  << "\n" \
<< std::string(30, '*') << "\n" << std::endl 

#define COUT(name) std::cout << name << std::endl 
#define SUCCESS std::cout << "SUCCESS" << std::endl 
#define FAILURE std::cout << "FAILURE" << std::endl 
#define TEST(name, boolean_value) \
LINE_SEPARATOR << name; \
boolean_value ? SUCCESS : FAILURE  

#define TOLERANCE 1.0E-12

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

void test_copy_position()
{
	TEST_HEADER_START("Test Copy Position");
	
	auto p1 = Position {1.0, 2.0, 3.0};
	Position p2;
	p2 = p1;
	
	TEST("Copy positon -> ", p1 == p2);
	TEST("Copy positon pointer-> ", &p1 != &p2); 
}

void test_material()
{
	TEST_HEADER_START("Test Material");
	double rho = 2.0;
	LinearMaterial m{rho};
	
	if (m.get_density() == rho)
		SUCCESS;
	else
		FAILURE;

	Position p {1.0, 0.0, 0.0};
	Position v {1.0, 2.0, 3.0};
	double r = 5.0;
	
	SphericParticle p1 = SphericParticle(p, v, r, m);
	
	COUT(&m);
	COUT(p1.material);
	if (p1.material->get_density() == rho)
		SUCCESS;
	else
		FAILURE;
	
	double vol = p1.geometry->get_volume();
	std::cout << "Vol =" << vol  << std::endl;
	double expected_vol = 4.0*M_PI*r*r*r/3.0;
    assert( std::abs(expected_vol - vol) < TOLERANCE);

	double mass = p1.get_mass(); 
	std::cout << "mass =" << mass  << std::endl;
	assert(std::abs(rho*expected_vol - mass) < TOLERANCE);
}
 
 
void test_particle_and_walls_instances()
{
	TEST_HEADER_START("Test Entities Instances");
	
	double r1 = 1.1;
	double r2 = 1.0;
	auto p1 = SphericParticle(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
	auto p2 = SphericParticle(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);
	
	std::cout << "Particles Position" << std::endl;
	p1.print_position();
	p2.print_position();
	
	/* check material density*/
	TEST("Material Density -> ", p1.material->density == 1.0);
	
	/*check particle volume */
	double vol = 4.0*M_PI*r1*r1*r1/3.0;
	TEST("Particle volume -> ", std:abs(p1.geometry->get_volume() - vol) < TOLERANCE);
	
	InfinityHorizontalWall w1{0.0};
	InfinityHorizontalWall w2{10.0};
	
	std::cout << "Walls" << std::endl;
	w1.print();
	w2.print();
	
	TEST("Wall 1 -> ", w1.geometry->point.y == 0.0);
	TEST("Wall 2 -> ", w2.geometry->point.y == 10.0);
}


void test_spheric_particle_distance()
{
	TEST_HEADER_START("Test Particle Distance");

	double r1 = 1.1;
	double r2 = 1.0;
	SphericParticle* p1 = new SphericParticle(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
	SphericParticle* p2 = new SphericParticle(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);
	
	std::vector<IParticle*> particles;
	particles.push_back(p1);
	particles.push_back(p2);

	int i = 0;
	double r_array[] = {r1, r2};
	for (auto p : particles)
	{
		Position position = p->position;
		double r = p->get_radius();
		TEST("Particle id = "<< i+1 << " radius -> ", r == r_array[i]);	
		TEST("Particle id = "<< i+1 << " type -> ", p->get_type() == Entity::SphericParticle);
		i++;
	}

	double d = Polymorphic::distance(particles.at(0), particles.at(1));
	
	TEST("Particles distance -> ", d <  0.0 ; std::abs(d) < 0.1 + TOLERANCE );
	
}


void test_contact()
{
	TEST_HEADER_START("Test Contact");
	
	double r1 = 1.1;
	double r2 = 1.0;
	SphericParticle* p1 = new SphericParticle(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
	SphericParticle* p2 = new SphericParticle(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);
	auto pair1 = std::make_shared<ContactPair>(ContactPair{p1, p2});
	
	ContactForce c {};
	c.add_force(pair1);
	std::cout << "\nparticles force = \n" << std::endl;
	Position* expected[] = {new Position{1.0, 0.0, 0.0}, new Position{1.0, 2.0, 0.0}};
	
	int i = 0;
	for (auto p : pair1->particles)
	{
		TEST("Postion -> ", p->position == *(expected[i]));
		p->print_force();
		i++;
	}
	
	std::cout << "\n Move particles  \n" << std::endl;
	double delta_t {0.01};
	p1->move(delta_t);
	p2->move(delta_t);
	
	i = 0;
	for (auto p : pair1->particles)
	{
		std::cout << " particle id = " << i << std::endl;
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
	ContactForce::stiffness = 1.0E4;
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
 	Integrator::integrate(domain, 0.001, 0.0, 0.02);
	std::cout << "End Collision" << std::endl;
}


void test_particles_wall_distance()
{

	TEST_HEADER_START( "Test Particle to Wall Distance");
	
	/* instantiating particles */
	SphericParticle* p1 = new SphericParticle(0.0, 1.0, 0.0, 10.0, 0.0, 0.0, 1.0);
	
	double y_wall_position = -5;
	InfinityHorizontalWall* w1 = new InfinityHorizontalWall(y_wall_position);

	double d1 = distance(p1, w1);
	std::cout << "D = " << d1 << std::endl;
	assert(std::abs(d1 + y_wall_position) < TOLERANCE);
}

void test_particles_to_wall()
{
	TEST_HEADER_START( "Test Particle to Wall Collision");
	
	/* instantiating particles */
	auto p1 = std::make_shared<SphericParticle>(SphericParticle(0.0, 1.1, 0.0, 0.0, -100.0, 0.0, 1.0));
	
	std::vector<std::shared_ptr<IParticle>> particles;
	particles.push_back(p1);
	
	/* Creating contacts collections*/
	auto w1 = std::make_shared<InfinityHorizontalWall>(InfinityHorizontalWall(0.0));
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

	/* Simulate*/
 	Integrator::integrate(domain, 0.001, 0.0, 0.02);
	std::cout << "End Wall Collision" << std::endl;
 	
}


int main()
{
	std::cout << "DEM PG simulator" << std::endl;
		
	test_types();
	test_copy_position();
	test_material();
	test_particle_and_walls_instances();
	test_spheric_particle_distance();
	test_contact();
	test_two_particles_collision();
	test_particles_wall_distance();
	test_particles_to_wall();
	
	return 0;
}

