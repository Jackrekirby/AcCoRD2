#include "vec_test.h"
#include "logger.h"
#include "math/vec3d.h"
#include "math/vec3b.h"
#include "math/vec3i.h"
#include "math/vec3.h"

namespace AcCoRD
{
	void VecTest()
	{
		using namespace math;

		Vec3d a(1, 2, 3);
		Vec3d b(4, 5, 6);
		LOG_INFO("a{} + b{} = {}", a, b, a + b);

		Vec3d c(3, 1, 5);
		LOG_INFO("a{} > c{} = {}", a, c, a > c);

		LOG_INFO("volume of {} = {}", c, c.Volume());

		Vec3d d(1.6, 4.8, -9.8);
		LOG_INFO("Vec3d{} to Vec3i{}", d, Vec3i(d));
	}
} // namespace AcCoRD