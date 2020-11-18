#include "pch.h"

#include "logger_test.h"
#include "json_test.h"
#include "random_test.h"
#include "vec_test.h"
#include "output_binary_test.h"
#include "event_queue_test.h"

#include "collision_surface_3d.h"
#include "collision_box_2d.h"
#include "collision_plane_x_3d.h"
#include "collision_3d.h"
#include "collision_box_3d.h"

#include "generating_plane_z_3d.h"
#include "generating_surface_3d.h"
#include "generating_box_2d.h"

#include "relation_box_2d.h"

void BoxCollisionTest()
{
	using namespace accord::shape;
	using namespace accord;

	collision::PlaneX_3D plane(10);
	collision::Box2D box(Vec2d(0, 0), Vec2d(10, 10));

	collision::Surface3D surface(std::make_unique<collision::PlaneX_3D>(10), std::make_unique<collision::Box2D>(box));

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

	//LOG_INFO(accord::JsonToPrettyString(j));
}

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	using namespace accord;
	using namespace accord::shape;
	
	Random::SetSeed();

	relation::Box2D b1({ 0, 0 }, { 10, 10 });
	relation::Box2D b2({ 5, 5 }, { 10, 10 });
	relation::Box2D b3({ -5, -5 }, { 20, 20 });

	relation::Surface3DShape& s1 = b1;
	relation::Surface3DShape& s2 = b2;
	relation::Surface3DShape& s3 = b3;

	LOG_DEBUG(b1.IsOverlapping(b2));
	LOG_DEBUG(b2.IsOverlapping(b1));
	LOG_DEBUG(b3.IsEnveloping(b1));
	LOG_DEBUG(b1.IsEnveloping(b3));

	LOG_DEBUG(s1.IsOverlapping(s2));
	LOG_DEBUG(s2.IsOverlapping(s1));
	LOG_DEBUG(s3.IsEnveloping(s1));
	LOG_DEBUG(s1.IsEnveloping(s3));

	//generating::Surface3D surface(std::make_unique<generating::PlaneZ3D>(10), std::make_unique<generating::Box2D>(Vec2d(0, 0), Vec2d(100, 100)));

	//for (int i = 0; i < 10; i++)
	//{
	//	LOG_DEBUG(surface.GeneratePointOnSurface());
	//}
	//

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
	//accord::EventQueueTest();
}