#include <catch.hpp>

#include <simulator/builder.hpp>

TEST_CASE("Simple Build of Particles") {

    Position pos {1, 2, 3};
    Velocity vel {4, 5, 6};
    double radius = 7;

    auto collection = ParticlesBuilder::create(
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

TEST_CASE("Build of 100 Particles") { 

    std::vector<Position> pos;
    std::vector<Velocity> vel;
    std::vector<double> radius;

    for (int j = 0; j < 100; ++j) {
        double i = j;
        pos.push_back(Position{i, i, i});
        vel.push_back(Velocity{i, i, i});
        radius.push_back(i);
    }

    auto collection = ParticlesBuilder::create(
        pos, // position
        vel, // velocity
        radius // radius
    );

    REQUIRE(collection.size() == 100);
    for (int j = 0; j < 100; ++j) {
        auto particle = collection[j];
        
        double i = j;

        REQUIRE(particle->position == Position{i, i, i});
        REQUIRE(particle->velocity == Velocity{i, i, i});

        Sphere* sphere = dynamic_cast<Sphere*>(particle->geometry);
        REQUIRE(sphere->get_radius() == i);
    }
}