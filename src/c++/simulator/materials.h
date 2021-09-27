#pragma once

#include "my_types.h"


struct IMaterial
{
	double density {};
	double young_modulus {};
	double poisson_ration {};
	
	virtual Material get_type() = 0;
	
	double get_density() const
	{
		return density;
	}
};

struct LinearMaterial : public IMaterial
{
	LinearMaterial(double density)
	{
		this->density = density;
	}
	
	LinearMaterial(double density, double young_modulus, double poisson_ration)  
	{
		this->density = density; 
		this->young_modulus = young_modulus;
		this->poisson_ration = poisson_ration;
	}
	
	Material get_type() override
	{
		return Material::LinearMaterial;
	}
};
