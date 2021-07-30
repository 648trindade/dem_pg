
struct IMaterial
{
	double density {};
	double young_modulus {};
	double poisson_ration {};
	
	IMaterial(double density) : density(density), young_modulus(0.0), poisson_ration(0.0)
	{
	}
};

struct LinearMaterial : public IMaterial
{
	LinearMaterial(double density) : IMaterial(density)
	{
	}
};
