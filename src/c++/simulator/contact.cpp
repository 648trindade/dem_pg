#include <simulator/contact.hpp>

ContactPair::ContactPair(SphericParticle &i, SphericParticle &j) {
  particles.push_back(std::make_shared<SphericParticle>(i));
  particles.push_back(std::make_shared<SphericParticle>(j));
}

ContactPair::ContactPair(SphericParticle *i, SphericParticle *j) {
  particles.push_back(std::make_shared<SphericParticle>(*i));
  particles.push_back(std::make_shared<SphericParticle>(*j));
}

ContactPair::ContactPair(std::shared_ptr<SphericParticle> i,
                         std::shared_ptr<SphericParticle> j) {
  particles.push_back(i);
  particles.push_back(j);
}

ContactBoundary::ContactBoundary(SphericParticle *p, Boundary *b) {
  particles.push_back(std::make_shared<SphericParticle>(*p));
  particles.push_back(std::make_shared<Boundary>(*b));
}

ContactBoundary::ContactBoundary(std::shared_ptr<SphericParticle> p,
                                 std::shared_ptr<Boundary> b) {
  particles.push_back(p);
  particles.push_back(b);
}

void ParticleCollection::add_contact_pair(ContactPair *pair) {
  particle_sets.push_back(std::make_shared<ContactPair>(*pair));
}

void ParticleCollection::add_contact_pair(std::shared_ptr<ContactPair> pair) {
  particle_sets.push_back(pair);
}

void ParticleCollection::add_contact_pair(ContactBoundary *pair) {
  particle_sets.push_back(std::make_shared<ContactBoundary>(*pair));
}

void ParticleCollection::add_contact_pair(
    std::shared_ptr<ContactBoundary> pair) {
  particle_sets.push_back(pair);
}
