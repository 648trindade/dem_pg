#pragma once

#include <simulator/boundaries.hpp>
#include <simulator/particle.hpp>

#include <memory>
#include <vector>

struct Contact {
    virtual std::shared_ptr<Entity> get_particle(int i) const = 0;
};

struct ParticleContact : public Contact {
public:
  ParticleContact(std::shared_ptr<Particle> i, std::shared_ptr<Particle> j);
  std::shared_ptr<Entity> get_particle(int i) const override;

private:
  std::vector<std::shared_ptr<Particle>> particles;
};

struct BoundaryContact : public Contact {
public:
  BoundaryContact(std::shared_ptr<Particle> p,
                  std::shared_ptr<Boundary> b);

  std::shared_ptr<Entity> get_particle(int i) const override;

private:
  std::vector<std::shared_ptr<Entity>> particles;
};

struct ContactCollection {
public:
  void add_contact_pair(std::shared_ptr<ParticleContact> const &pair);
  void add_contact_pair(std::shared_ptr<BoundaryContact> const &pair);
  void clear_contacts();

public:
  std::vector<std::shared_ptr<Contact>> particle_sets;
};
