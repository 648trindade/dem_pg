#pragma once

#include <simulator/domain.hpp>

#include <iostream>
#include <functional>

void integrate(
	Domain& domain,
	double delta_t,
	double initial_time,
	double final_time,
	std::function<void(double, std::vector<std::shared_ptr<IParticle>> const&)> const& callback);
