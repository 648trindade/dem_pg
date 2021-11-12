#pragma once

#include <simulator/boundaries.hpp>
#include <simulator/particle.hpp>

#include <memory>
#include <vector>

struct Contact {
    virtual std::shared_ptr<IParticle> get_particle(int i) const = 0;
};

struct ParticleContact : public Contact {
public:
  ParticleContact(SphericParticle &i, SphericParticle &j);
  ParticleContact(SphericParticle *i, SphericParticle *j);
  ParticleContact(std::shared_ptr<SphericParticle> i,
                  std::shared_ptr<SphericParticle> j);

  std::shared_ptr<IParticle> get_particle(int i) const;

public:
  std::vector<std::shared_ptr<IParticle>> particles;
};

struct BoundaryContact : public Contact {
public:
  BoundaryContact(SphericParticle *p, Boundary *b);
  BoundaryContact(std::shared_ptr<SphericParticle> p,
                  std::shared_ptr<Boundary> b);

  std::shared_ptr<IParticle> get_particle(int i) const override;

public:
  std::vector<std::shared_ptr<IParticle>> particles;
};

struct ContactCollection {
public:
  void add_contact_pair(std::shared_ptr<ParticleContact> const &pair);
  void add_contact_pair(std::shared_ptr<BoundaryContact> const &pair);

public:
  std::vector<std::shared_ptr<Contact>> particle_sets;
};
