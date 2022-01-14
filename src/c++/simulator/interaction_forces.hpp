#pragma once

#include <simulator/analitic_geometry.hpp>
#include <simulator/contact.hpp>
#include <simulator/particle.hpp>

#include <iostream>
#include <memory>

class InteractionForceCalculator {
public:
  virtual void add_force(std::shared_ptr<Contact> particle_set) = 0;
};

struct ContactForceCalculator : public InteractionForceCalculator {
public:
  ContactForceCalculator(double stiffness);

  void add_force(std::shared_ptr<Contact> particle_set) override;

private:
  double stiffness = 1.0;
};

struct InteractionForceCollection {
public:
  void add_interaction_force(std::shared_ptr<ContactForceCalculator> interaction_force);

public:
  std::vector<std::shared_ptr<InteractionForceCalculator>> interaction_forces;
};

struct InteractionForceAssembler {
public:
  InteractionForceAssembler();
  InteractionForceAssembler(
      ContactCollection &collection,
      InteractionForceCollection &interaction_forces_collection);

void search_contacts(
    std::vector<std::shared_ptr<Entity>> const& particles,
    std::vector<std::shared_ptr<Boundary>> const& boundaries
);

public:
  ContactCollection collection;
  InteractionForceCollection interaction_forces_collection;
};
