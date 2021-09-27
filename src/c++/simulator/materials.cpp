#include <simulator/materials.hpp>

double IMaterial::get_density() const
{
	return density;
}

LinearMaterial::LinearMaterial(double density)
{
	this->density = density;
}

LinearMaterial::LinearMaterial(double density, double young_modulus, double poisson_ration)  
{
	this->density = density; 
	this->young_modulus = young_modulus;
	this->poisson_ration = poisson_ration;
}

Material LinearMaterial::get_type()
{
	return Material::LinearMaterial;
}
