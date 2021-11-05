#pragma once

#include <simulator/my_types.hpp>

struct IMaterial {
public:
  virtual Material get_type() = 0;
  double get_density() const;

public:
  double density;
  double young_modulus;
  double poisson_ration;
};

struct LinearMaterial : public IMaterial {
  LinearMaterial(double density);
  LinearMaterial(double density, double young_modulus, double poisson_ration);
  Material get_type() override;
};
