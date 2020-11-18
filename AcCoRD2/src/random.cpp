#include "random.h"

#include <random>

namespace accord
{
	pcg32 Random::s_rng;

	void Random::SetSeed(pcg32::state_type seed)
	{
		Random::s_rng.seed(seed);
	}

	void Random::SetSeed()
	{
		pcg_extras::seed_seq_from<std::random_device> seed_source;
		Random::s_rng = seed_source;
	}

	pcg32& Random::GetGenerator()
	{
		return Random::s_rng;
	}

	double Random::GenerateExponential(double mean)
	{
		std::exponential_distribution<double> distribution(mean);
		return distribution(Random::s_rng);
	}

	int Random::GeneratePoisson(double mean)
	{
		std::poisson_distribution<int> distribution(mean);
		return distribution(Random::s_rng);
	}

	double Random::GenerateNormal(double mean, double std)
	{
		std::normal_distribution<double> distribution(mean, std);
		return distribution(Random::s_rng);
	}

	double Random::GenerateTriangular()
	{
		double urv = (double) s_rng() / UINT32_MAX;

		return (urv < 0.5) ? std::sqrt(2 * urv) : (2 - std::sqrt(2 * (1 - urv)));
	}

	// Value will be in range [0,1)
	double Random::GenerateRealUniform(double lower_bound, double upper_bound)
	{
		std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);
		return distribution(Random::s_rng);
	}

	int Random::GenerateIntUniform(int lower_bound, int upper_bound)
	{
		std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);
		return distribution(Random::s_rng);
	}

} // namespace accord