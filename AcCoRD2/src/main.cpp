#include "pch.h"

#include "logger_test.h"
#include "json_test.h"
#include "random_test.h"
#include "vec_test.h"
#include "output_binary_test.h"
#include "event_queue_test.h"

#include "shapes/surface_3d.h"
#include "shapes/box_2d.h"
#include "shapes/plane_x_3d.h"
#include "shapes/collision_3d.h"

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	LOG_INFO("hi");

	using namespace accord::shapes;
	using namespace accord::math;

	PlaneX_3D plane(5);
	Box2D box(Vec2d(0, 0), Vec2d(10, 10));

	Surface3D surface(std::make_unique<PlaneX_3D>(5), std::make_unique<Box2D>(box));

	accord::math::Vec3d origin(0, 10, 0);
	accord::math::Vec3d end(7, 10, 0);

	LOG_INFO("origin = {}, end = {}", origin, end);
	LOG_INFO(surface.CalculateCollisionDataWithNegativeFace(origin, end));

	//accord::math::EnumToString(accord::math::Axis3D::z);

	//LOG_INFO(accord::math::Axis3D::z);

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
	//accord::EventQueueTest();
}