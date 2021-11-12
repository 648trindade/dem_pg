#include <simulator/interaction_forces.hpp>

ContactForceCalculator::ContactForceCalculator(double stiffness) : stiffness(stiffness) {}

void ContactForceCalculator::add_force(std::shared_ptr<Contact> contact) {
    // TODO: Generalize to any type of contact
    auto p1 = contact->get_particle(0);
    auto p2 = contact->get_particle(1);
    double d = Polymorphic::distance(p1.get(), p2.get());

    if (d >= 0.0) {
        return;
    }

    Vector direction = p1->position - p2->position;
    Force force = direction * (stiffness / direction.norm());

    // action and reaction
    p2->add_force(-force);
    p1->add_force(force);
}

void InteractionForceCollection::add_interaction_force(
    std::shared_ptr<ContactForceCalculator> interaction_force) {
  interaction_forces.push_back(interaction_force);
}

InteractionForceAssembler::InteractionForceAssembler() {}

InteractionForceAssembler::InteractionForceAssembler(
        ContactCollection &collection,
        InteractionForceCollection &interaction_forces_collection)
    : collection(collection),
      interaction_forces_collection(interaction_forces_collection) {}
