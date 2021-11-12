#pragma once

#include <simulator/analitic_geometry.hpp>
#include <simulator/contact.hpp>
#include <simulator/particle.hpp>

#include <iostream>
#include <memory>

struct InteractionForce {
  virtual void add_force(std::shared_ptr<Contact> paticle_set);
};

struct ContactForce : public InteractionForce {
public:
  ContactForce(double stiffness);

  void add_force(std::shared_ptr<Contact> paticle_set);
  void add_force(ParticleContact *contact_set);
  void add_force(std::shared_ptr<ParticleContact> contact_set);

private:
  double stiffness = 1.0;
};

struct InteractionForceCollection {
public:
  void add_interaction_force(InteractionForce *interaction_force);
  void
  add_interaction_force(std::shared_ptr<InteractionForce> interaction_force);
  void add_interaction_force(ContactForce *interaction_force);
  void add_interaction_force(std::shared_ptr<ContactForce> interaction_force);

public:
  std::vector<std::shared_ptr<InteractionForce>> interaction_forces;
};

struct InteractionForceAssembler {
public:
  InteractionForceAssembler();
  InteractionForceAssembler(
          ContactCollection &collection,
          InteractionForceCollection &interaction_forces_collection);

public:
  ContactCollection collection;
  InteractionForceCollection interaction_forces_collection;
};
