#pragma once

#include <iostream>
#include <simulator/geometry.hpp>
#include <simulator/materials.hpp>
#include <simulator/mechanics.hpp>
#include <simulator/my_types.hpp>

class Entity {
public:
  virtual EntityType get_type() = 0;
  virtual double get_radius() const = 0;

  void set_material(IMaterial *material) { this->material = material; }

  void set_geometry(IGeometry *g) { this->geometry = g; }

  double get_density();
  Position get_position() const;
  double get_mass() const;
  void add_force(const Force &force);
  void reset_force();
  void move(double delta_t);
  void print_position() const;
  void print_velocity() const;
  void print_force() const;

public:
  Position position{0.0, 0.0, 0.0};
  Velocity velocity{0.0, 0.0, 0.0};
  Force force{0.0, 0.0, 0.0};
  IMaterial *material;
  IGeometry *geometry;
};

struct SphericParticle : public Entity {
  SphericParticle(double x, double y, double z, double vx, double vy, double vz,
                  double r, double rho = 1.0);
  SphericParticle(Position p, Velocity v, double r, LinearMaterial *m);
  ~SphericParticle();
  EntityType get_type() override;
  double get_radius() const override;
};
