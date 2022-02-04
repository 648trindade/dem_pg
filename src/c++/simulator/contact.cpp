#include <simulator/contact.hpp>

ParticleContact::ParticleContact(std::shared_ptr<Particle> i,
                                 std::shared_ptr<Particle> j) {
  particles.push_back(i);
  particles.push_back(j);
}

std::shared_ptr<Entity> ParticleContact::get_particle(int i) const {
  return this->particles.at(i);
}

BoundaryContact::BoundaryContact(std::shared_ptr<Particle> p,
                                 std::shared_ptr<Boundary> b) {
  particles.push_back(p);
  particles.push_back(b);
}

std::shared_ptr<Entity> BoundaryContact::get_particle(int i) const
{
    // TODO: Verify if this makes sense and overhaul architecture for particles from contacts
    return this->particles.at(i);
}

void ContactCollection::add_contact_pair(std::shared_ptr<ParticleContact> const& pair) {
  particle_sets.push_back(pair);
}

void ContactCollection::add_contact_pair(
    std::shared_ptr<BoundaryContact> const& pair) {
  particle_sets.push_back(pair);
}

void ContactCollection::clear_contacts()
{
  particle_sets.clear();
}
