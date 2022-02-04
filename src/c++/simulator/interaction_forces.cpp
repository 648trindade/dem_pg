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
    // TODO: improve force calculation
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

void InteractionForceAssembler::search_contacts(
    std::vector<std::shared_ptr<Particle>> const& particles,
    std::vector<std::shared_ptr<Boundary>> const& boundaries
)
{
  this->collection.clear_contacts();

  for (int i = 0; i < particles.size(); i++)
  {
    auto& first_particle = particles[i];
    for (int j = i + 1; j < particles.size(); j++)
    {
      auto& second_particle = particles[j];
      this->collection.add_contact_pair(std::make_shared<ParticleContact>(first_particle, second_particle));
    }
  }

  for (int i = 0; i < particles.size(); i++)
  {
    auto& first_particle = particles[i];
    for (int j = 0; j < boundaries.size(); j++)
    {
      auto& boundary = boundaries[j];
      this->collection.add_contact_pair(std::make_shared<BoundaryContact>(first_particle, boundary));
    }
  }
}
