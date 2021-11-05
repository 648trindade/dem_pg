#include <simulator/particle.hpp>

double IParticle::get_density() { return material->get_density(); }

Position IParticle::get_position() const { return this->position; }

double IParticle::get_mass() const {
  return this->geometry->get_volume() * this->material->get_density();
}

void IParticle::add_force(const Force &force) { this->force += force; }

void IParticle::reset_force() {
  force.x = 0.0;
  force.y = 0.0;
  force.z = 0.0;
}

void IParticle::move(double delta_t) {
  this->velocity += this->force * (delta_t / this->get_mass());
  this->position += this->velocity * delta_t;
  this->reset_force();
}

void IParticle::print_position() const {
  std::cout << " {" << position.x << ", " << position.y << ", " << position.z
            << "} ";
}

void IParticle::print_velocity() const {
  std::cout << " {" << velocity.x << ", " << velocity.y << ", " << velocity.z
            << "} ";
}

void IParticle::print_force() const {
  std::cout << " {" << this->force.x << ", " << this->force.y << ", "
            << this->force.z << "} ";
}

SphericParticle::SphericParticle(double x, double y, double z, double vx,
                                 double vy, double vz, double r, double rho) {
  position = Position{x, y, z};
  velocity = Velocity{vx, vy, vz};
  geometry = new Sphere(r);
  material = new LinearMaterial(rho);
}

SphericParticle::SphericParticle(Position p, Velocity v, double r,
                                 LinearMaterial *m) {
  position = p;
  velocity = v;
  geometry = new Sphere(r);
  material = m;
}

SphericParticle::~SphericParticle() {
  // delete material;
  // delete geometry;
}

Entity SphericParticle::get_type() { return Entity::SphericParticle; }

double SphericParticle::get_radius() const {
  return this->geometry->get_radius();
}
