#include <catch.hpp>

#include <simulator/analitic_geometry.hpp>
#include <simulator/boundaries.hpp>
#include <simulator/domain.hpp>
#include <simulator/integrator.hpp>
#include <simulator/interaction_forces.hpp>
#include <simulator/my_types.hpp>
#include <simulator/particle.hpp>

#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace geometric;

#define TOLERANCE 1.0E-4

TEST_CASE("Test Entities Types") {
  SphericParticle p1{1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.1};

  REQUIRE(p1.get_type() == EntityType::SphericParticle);
}

TEST_CASE("Test Copy Position") {
  auto p1 = Position{1.0, 2.0, 3.0};
  Position p2;
  p2 = p1;

  REQUIRE((p1 == p2));
  REQUIRE(&p1 != &p2);
}

TEST_CASE("Test Material") {
  double rho = 2.0;
  LinearMaterial m{rho};
  REQUIRE(m.get_density() == rho);

  Position p{1.0, 0.0, 0.0};
  Position v{1.0, 2.0, 3.0};
  double r = 5.0;
  SphericParticle p1 = SphericParticle(p, v, r, &m);
  REQUIRE(p1.material->get_density() == rho);

  double vol = p1.geometry->get_volume();
  double expected_vol = 4.0 * M_PI * r * r * r / 3.0;
  REQUIRE(std::abs(expected_vol - vol) < TOLERANCE);

  double mass = p1.get_mass();
  REQUIRE(std::abs(rho * expected_vol - mass) < TOLERANCE);
}

TEST_CASE("Test Entities Instances") {
  double r1 = 1.1;
  double r2 = 1.0;
  auto p1 = SphericParticle(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
  auto p2 = SphericParticle(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);

  REQUIRE(p1.material->density == 1.0);
  double vol = 4.0 * M_PI * r1 * r1 * r1 / 3.0;
  REQUIRE(std::abs(p1.geometry->get_volume() - vol) < TOLERANCE);

  InfinityHorizontalWall w1{0.0};
  InfinityHorizontalWall w2{10.0};
  REQUIRE(w1.geometry->point.y == 0.0);
  REQUIRE(w2.geometry->point.y == 10.0);
}

TEST_CASE("Test Particle Distance") {
  double r1 = 1.1;
  double r2 = 1.0;
  SphericParticle p1(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
  SphericParticle p2(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);

  std::vector<Entity *> particles;
  particles.push_back(&p1);
  particles.push_back(&p2);

  int i = 0;
  double r_array[] = {r1, r2};
  for (auto const &p : particles) {
    double r = p->get_radius();

    REQUIRE(r == r_array[i]);
    REQUIRE(p->get_type() == EntityType::SphericParticle);

    i++;
  }

  double d = Polymorphic::distance(particles.at(0), particles.at(1));
  REQUIRE(std::abs(d) < 0.1 + TOLERANCE);
}

TEST_CASE("Test Contact") {
  double r1 = 1.1;
  double r2 = 1.0;
  auto p1 = std::make_shared<SphericParticle>(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, r1);
  auto p2 = std::make_shared<SphericParticle>(1.0, 2.0, 0.0, 0.0, 0.0, 0.0, r2);
  auto pair1 = std::make_shared<ParticleContact>(ParticleContact{p1, p2});
  auto contact_force = ContactForceCalculator{1.0};
  contact_force.add_force(pair1);

  REQUIRE((p1->position == Position{1.0, 0.0, 0.0}));
  REQUIRE((p2->position == Position{1.0, 2.0, 0.0}));

  double delta_t = 0.1;
  p1->move(delta_t);
  p2->move(delta_t);

  REQUIRE((p1->position.x == 1.0));
  REQUIRE((p1->position.y < 0.0));
  REQUIRE((p1->position.z == 0.0));

  REQUIRE((p2->position.x == 1.0));
  REQUIRE((p2->position.y > 2.0));
  REQUIRE((p2->position.z == 0.0));
}

TEST_CASE("Test Particle Collision") {
  /* Instantiating particles */
  auto p1 = std::make_shared<SphericParticle>(
      // Position [x, y, z]:
      1.0, 0.0, 0.0,
      // Velocity [x, y, z]:
      10.0, 0.0, 0.0,
      // Radius:
      1.0);
  auto p2 = std::make_shared<SphericParticle>(
      // Position [x, y, z]:
      3.1, 0.0, 0.0,
      // Velocity [x, y, z]:
      -10.0, 0.0, 0.0,
      // Radius:
      1.0);
  auto particles = std::vector<std::shared_ptr<Entity>>{{p1, p2}};

  /* Creating contacts collections */
  auto contact_collection = ContactCollection{};
// contact_collection.add_contact_pair(std::make_shared<ParticleContact>(p1, p2));

  /* Setting interaction forces */
  auto force_collection = InteractionForceCollection{};
  force_collection.add_interaction_force(std::make_shared<ContactForceCalculator>(1e+4));

  /* Creating Simulation domain */
  InteractionForceAssembler assembler(contact_collection, force_collection);
  Domain domain{particles, assembler};

  /* Simulate */
  double final_time = 0.0;
  integrate(domain, 0.001, 0.0, 0.02,
            [&](double time,
                std::vector<std::shared_ptr<Entity>> const &particles) {
              if (std::abs(time - 0.001) < 1e-8) {
                REQUIRE(std::abs(p1->position.x - 1.01) < TOLERANCE);
                REQUIRE(std::abs(p2->position.x - 3.09) < TOLERANCE);

                REQUIRE(std::abs(p1->velocity.x - 10.0) < TOLERANCE);
                REQUIRE(std::abs(p2->velocity.x - -10.0) < TOLERANCE);
              }

              if (std::abs(time - 0.007) < 1e-8) {
                REQUIRE(std::abs(p1->position.x - 1.06761) < TOLERANCE);
                REQUIRE(std::abs(p2->position.x - 3.03239) < TOLERANCE);

                REQUIRE(std::abs(p1->velocity.x - 7.61268) < TOLERANCE);
                REQUIRE(std::abs(p2->velocity.x - -7.61268) < TOLERANCE);
              }

              if (std::abs(time - 0.02) < 1e-8) {
                REQUIRE(std::abs(p1->position.x - 0.985141) < TOLERANCE);
                REQUIRE(std::abs(p2->position.x - 3.11486) < TOLERANCE);

                REQUIRE(std::abs(p1->velocity.x - -11.4859) < TOLERANCE);
                REQUIRE(std::abs(p2->velocity.x - 11.4859) < TOLERANCE);
              }

              final_time = time;
            });
  REQUIRE(std::abs(final_time - 0.02) < TOLERANCE);
}

TEST_CASE("Test Particle to Wall Distance") {
  auto p1 = SphericParticle(
      // Position [x, y, z]:
      0.0, 1.0, 0.0,
      // Velocity [x, y, z]:
      10.0, 0.0, 0.0,
      // Radius:
      1.0);
  auto w1 = InfinityHorizontalWall(-5.);
  double d = distance(p1, w1);
  REQUIRE(std::abs(d - 5.0) < TOLERANCE);
}

TEST_CASE("Test Particle to Wall Collision") {
  /* Instantiating particles */
  auto p1 = std::make_shared<SphericParticle>(
      // Position [x, y, z]:
      0.0, 1.1, 0.0,
      // Velocity [x, y, z]:
      0.0, -100.0, 0.0,
      // Radius:
      1.0);

  std::vector<std::shared_ptr<Entity>> particles;
  particles.push_back(p1);

  /* Creating contacts collections */
  auto w1 = std::make_shared<InfinityHorizontalWall>(0.0);
  auto pair = std::make_shared<BoundaryContact>(p1, w1);

  particles.push_back(w1);

  ContactCollection collection;
  // collection.add_contact_pair(pair);

  /* Setting intertaction forces */
  auto contact_force = std::make_shared<ContactForceCalculator>(1e+5);
  InteractionForceCollection int_force_collection;
  int_force_collection.add_interaction_force(contact_force);

  /* Creating Simulation domain */
  auto assembler = InteractionForceAssembler(collection, int_force_collection);
  Domain domain{particles, assembler};

  /* Simulate */
  double final_time = 0.0;
  integrate(
      domain, 0.001, 0.0, 0.02,
      [&](double time, std::vector<std::shared_ptr<Entity>> particles) {
        if (std::abs(time - 0.001) < 1e-8) {
          REQUIRE(std::abs(p1->position.y - 1.0) < TOLERANCE);
        }

        if (std::abs(time - 0.005) < 1e-8) {
          REQUIRE(std::abs(p1->position.y - 0.74323) < TOLERANCE);
        }

        if (std::abs(time - 0.01) < 1e-8) {
          REQUIRE(std::abs(p1->position.y - 0.959437) < TOLERANCE);
        }

        if (std::abs(time - 0.015) < 1e-8) {
          REQUIRE(std::abs(p1->position.y - 1.53373) < TOLERANCE);
        }

        if (std::abs(time - 0.02) < 1e-8) {
          REQUIRE(std::abs(p1->position.y - 2.10803) < TOLERANCE);
        }
        final_time = time;
      });
  REQUIRE(std::abs(final_time - 0.02) < TOLERANCE);
}
