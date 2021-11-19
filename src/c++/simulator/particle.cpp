#include <simulator/particle.hpp>

double Entity::get_density() { return material->get_density(); }

Position Entity::get_position() const { return this->position; }

double Entity::get_mass() const {
  return this->geometry->get_volume() * this->material->get_density();
}

void Entity::add_force(const Force &force) { this->force += force; }

void Entity::reset_force() {
  force.x = 0.0;
  force.y = 0.0;
  force.z = 0.0;
}

void Entity::move(double delta_t) {
  this->velocity += this->force * (delta_t / this->get_mass());
  this->position += this->velocity * delta_t;
  this->reset_force();
}

void Entity::print_position() const {
  std::cout << " {" << position.x << ", " << position.y << ", " << position.z
            << "} ";
}

void Entity::print_velocity() const {
  std::cout << " {" << velocity.x << ", " << velocity.y << ", " << velocity.z
            << "} ";
}

void Entity::print_force() const {
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

EntityType SphericParticle::get_type() { return EntityType::SphericParticle; }

double SphericParticle::get_radius() const {
  return this->geometry->get_radius();
}
