#pragma once

enum class Entity
{
	IParticle,
	SphericParticle,
	Boundary,
	Wall
};

enum class Set
{
	ContactPair,
	ContactBoundary
};

enum class Material
{
	IMaterial,
	LinearMaterial
};
