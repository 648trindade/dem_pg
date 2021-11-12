﻿#include <simulator/interaction_forces.hpp>

ContactForce::ContactForce(double stiffness) : stiffness(stiffness) {}

void InteractionForce::add_force(std::shared_ptr<Contact> paticle_set) {}

void ContactForce::add_force(std::shared_ptr<Contact> paticle_set) {
  ParticleContact *contact_pair_ptr =
      reinterpret_cast<ParticleContact *>(paticle_set.get());
  add_force(contact_pair_ptr);
}

void ContactForce::add_force(ParticleContact *contact_set) {
  add_force(std::make_shared<ParticleContact>(*contact_set));
}

void ContactForce::add_force(std::shared_ptr<ParticleContact> contact_set) {

  auto &p1 = contact_set->particles.at(0);
  auto &p2 = contact_set->particles.at(1);
  double d = Polymorphic::distance(p1.get(), p2.get());

  if (d >= 0.0) {
    return;
  }

  Vector direction = p1->position - p2->position;
  Force force = direction * (stiffness / direction.norm());

  // action and reaction
  p2->add_force(-force);
  p1->add_force(force);
};

void InteractionForceCollection::add_interaction_force(
    InteractionForce *interaction_force) {
  add_interaction_force(std::make_shared<InteractionForce>(*interaction_force));
}

void InteractionForceCollection::add_interaction_force(
    std::shared_ptr<InteractionForce> interaction_force) {
  interaction_forces.push_back(interaction_force);
}

void InteractionForceCollection::add_interaction_force(
    ContactForce *interaction_force) {
  add_interaction_force(std::make_shared<ContactForce>(*interaction_force));
}

void InteractionForceCollection::add_interaction_force(
    std::shared_ptr<ContactForce> interaction_force) {
  interaction_forces.push_back(interaction_force);
}

InteractionForceAssembler::InteractionForceAssembler() {}

InteractionForceAssembler::InteractionForceAssembler(
        ContactCollection &collection,
        InteractionForceCollection &interaction_forces_collection)
    : collection(collection),
      interaction_forces_collection(interaction_forces_collection) {}
