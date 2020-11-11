#pragma once
#include "pcg/pcg_random.hpp"

namespace AcCoRD
{
	class Random
	{
	public:
		static void SetSeed(pcg32::state_type seed);

		static void SetSeed();

		static pcg32& GetGenerator();

		static double GenerateExponential(double mean);

		static int GeneratePoisson(double mean);

		static double GenerateNormal(double mean, double std);

		static double GenerateTriangular();

		static double GenerateRealUniform();

		static int GenerateIntUniform(int lower_bound, int upper_bound);

	private:
		static pcg32 s_rng;
	};
} // namespace AcCoRD