#include <simulator/contact.hpp>

ParticleContact::ParticleContact(SphericParticle &i, SphericParticle &j) {
  particles.push_back(std::make_shared<SphericParticle>(i));
  particles.push_back(std::make_shared<SphericParticle>(j));
}

ParticleContact::ParticleContact(SphericParticle *i, SphericParticle *j) {
  particles.push_back(std::make_shared<SphericParticle>(*i));
  particles.push_back(std::make_shared<SphericParticle>(*j));
}

ParticleContact::ParticleContact(std::shared_ptr<SphericParticle> i,
                                 std::shared_ptr<SphericParticle> j) {
  particles.push_back(i);
  particles.push_back(j);
}

std::shared_ptr<Entity> ParticleContact::get_particle(int i) const {
  return this->particles.at(i);
}

BoundaryContact::BoundaryContact(SphericParticle *p, Boundary *b) {
  particles.push_back(std::make_shared<SphericParticle>(*p));
  particles.push_back(std::make_shared<Boundary>(*b));
}

BoundaryContact::BoundaryContact(std::shared_ptr<SphericParticle> p,
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
