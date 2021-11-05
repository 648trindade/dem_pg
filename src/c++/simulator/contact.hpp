#pragma once

#include <simulator/boundaries.hpp>
#include <simulator/particle.hpp>

#include <memory>
#include <vector>

struct ParticleSet {};

struct ContactPair : public ParticleSet {
public:
  ContactPair(SphericParticle &i, SphericParticle &j);
  ContactPair(SphericParticle *i, SphericParticle *j);
  ContactPair(std::shared_ptr<SphericParticle> i,
              std::shared_ptr<SphericParticle> j);

public:
  std::vector<std::shared_ptr<IParticle>> particles;
};

struct ContactBoundary : public ParticleSet {
public:
  ContactBoundary(SphericParticle *p, Boundary *b);
  ContactBoundary(std::shared_ptr<SphericParticle> p,
                  std::shared_ptr<Boundary> b);

public:
  std::vector<std::shared_ptr<IParticle>> particles;
};

struct ParticleCollection {
public:
  void add_contact_pair(ContactPair *pair);
  void add_contact_pair(std::shared_ptr<ContactPair> pair);
  void add_contact_pair(ContactBoundary *pair);
  void add_contact_pair(std::shared_ptr<ContactBoundary> pair);

public:
  std::vector<std::shared_ptr<ParticleSet>> particle_sets;
};
