#include "random_test.h"
#include "random.h"
#include "logger.h"

namespace AcCoRD
{
	void RandomTest()
	{
		AcCoRD::Random::SetSeed();

		LOG_INFO(AcCoRD::Random::GenerateRealUniform());
		LOG_INFO(AcCoRD::Random::GenerateExponential(1));
		LOG_INFO(AcCoRD::Random::GenerateIntUniform(0, 100));
		LOG_INFO(AcCoRD::Random::GenerateNormal(0, 1));
		LOG_INFO(AcCoRD::Random::GeneratePoisson(4.7));
		LOG_INFO(AcCoRD::Random::GenerateTriangular());
	}
} // namespace AcCoRD