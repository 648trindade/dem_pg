#include <catch.hpp>

#include <simulator/builder.hpp>

TEST_CASE("Simple Build of Particles") {

    Position pos {1, 2, 3};
    Velocity vel {4, 5, 6};
    double radius = 7;

    auto collection = Builder::create(
        {pos}, // position
        {vel}, // velocity
        {radius} // radius
    );

    REQUIRE(collection.size() == 1);
    auto particle = collection[0];

    REQUIRE(particle->position == pos);
    REQUIRE(particle->velocity == vel);

    Sphere* sphere = dynamic_cast<Sphere*>(particle->geometry);
    REQUIRE(sphere->get_radius() == radius);
}