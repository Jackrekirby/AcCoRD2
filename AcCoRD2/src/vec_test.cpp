#include "pch.h"
#include "vec_test.h"
//#include "logger.h"

#include "vec3d.h"
#include "vec3b.h"
#include "vec3i.h"
#include "vec3.h"

#include "vec2d.h"
#include "vec2b.h"
#include "vec2i.h"
#include "vec2.h"

namespace accord
{
	void VecTest()
	{
		{
			Vec3d a(1, 2, 3);
			Vec3d b(4, 5, 6);
			LOG_INFO("a{} + b{} = {}", a, b, a + b);

			Vec3d c(3, 1, 5);
			LOG_INFO("a{} > c{} = {}", a, c, a > c);

			LOG_INFO("volume of {} = {}", c, c.Volume());

			Vec3d d(1.6, 4.8, -9.8);
			LOG_INFO("Vec3d{} to Vec3i{}", d, Vec3i(static_cast<int>(d.x), static_cast<int>(d.y), static_cast<int>(d.z)));
		}
		{
			Vec2d a(1, 2);
			Vec2d b(4, 5);
			LOG_INFO("a{} + b{} = {}", a, b, a + b);

			Vec2d c(3, 1);
			LOG_INFO("a{} > c{} = {}", a, c, a > c);
			
			LOG_INFO("volume of {} = {}", c, c.Area());

			Vec2d d(1.6, -4.8);
			LOG_INFO("Vec2d{} to Vec2i{}", d, Vec2i(static_cast<int>(d.x), static_cast<int>(d.y)));
		}
	}
} // namespace accord