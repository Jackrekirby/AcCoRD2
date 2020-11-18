#include "pch.h"

#include "logger_test.h"
#include "json_test.h"
#include "random_test.h"
#include "vec_test.h"
#include "output_binary_test.h"
#include "event_queue_test.h"

#include "surface_3d.h"
#include "collision_box_2d.h"
#include "plane_x_3d.h"
#include "collision_3d.h"
#include "collision_box_3d.h"

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	using namespace accord::shape;
	using namespace accord;

	PlaneX_3D plane(10);
	collision::Box2D box(Vec2d(0, 0), Vec2d(10, 10));

	Surface3D surface(std::make_unique<PlaneX_3D>(10), std::make_unique<collision::Box2D>(box));

	accord::Vec3d origin(5, 5, 5);
	accord::Vec3d end(-19, -13, 12);
	///accord::Vec3d end(-1.5, 0, 0);

	LOG_INFO("origin = {}, end = {}", origin, end);
	//LOG_INFO(surface.CalculateCollisionDataWithNegativeFace(origin, end));

	//Box3D box3d(Vec3d(-1, -1, -1), Vec3d(2, 2, 2));
	collision::Box3D box3d(Vec3d(0, 0, 0), Vec3d(10, 10, 10));

	LOG_INFO(box3d.CalculateInternalCollisionData(origin, end));
	//LOG_INFO(box3d.CalculateExternalCollisionData(origin, end));
	accord::Json j;
	j = box3d;

	//LOG_INFO(box3d.GetFaces().at(3).CalculateCollisionDataWithNegativeFace(origin, end));


	//LOG_INFO(accord::JsonToPrettyString(j));

	//LOG_INFO(box3d);

	//accord::EnumToString(accord::Axis3D::z);

	//LOG_INFO(accord::Axis3D::z);

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
	//accord::EventQueueTest();
}