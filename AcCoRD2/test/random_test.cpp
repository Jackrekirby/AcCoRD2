#include "random_test.h"
#include "random.h"
#include "logger.h"

namespace accord
{
	void RandomTest()
	{
		accord::Random::SetSeed();

		LOG_INFO(accord::Random::GenerateRealUniform());
		LOG_INFO(accord::Random::GenerateExponential(1));
		LOG_INFO(accord::Random::GenerateIntUniform(0, 100));
		LOG_INFO(accord::Random::GenerateNormal(0, 1));
		LOG_INFO(accord::Random::GeneratePoisson(4.7));
		LOG_INFO(accord::Random::GenerateTriangular());
	}
} // namespace accord