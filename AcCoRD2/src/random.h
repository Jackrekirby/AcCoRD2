#pragma once
#include "pcg/pcg_random.hpp"

namespace accord
{
	class Random
	{
	public:
		static void SetSeed(pcg32::state_type seed);

		static void SetSeed();

		static pcg32& GetGenerator();

		static double GenerateExponential(double mean);

		static int GeneratePoisson(double mean);

		static double GenerateNormal(double mean = 0.0, double std = 1.0);

		static double GenerateTriangular();

		static double GenerateRealUniform(double lower_bound = 0.0, double upper_bound = 1.0);

		static int GenerateIntUniform(int lower_bound, int upper_bound);

	private:
		static pcg32 s_rng;
	};
} // namespace accord