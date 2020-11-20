#include "pch.h"
#include "shape_test.h"

#include "collision_surface_3d.h"
#include "collision_box_2d.h"
#include "collision_plane_x_3d.h"
#include "collision_3d.h"
#include "collision_box_3d.h"

#include "generating_plane_z_3d.h"
#include "generating_surface_3d.h"
#include "generating_box_2d.h"
#include "generating_box_3d.h"
#include "generating_plane_3d_factory.h"

#include "relation_box_2d.h"
#include "relation_box_3d.h"
#include "relation_circle.h"
#include "relation_box_surface_3d.h"


namespace accord
{
	void ShapeCollisionTest()
	{
		using namespace accord::shape;
		using namespace accord;

		collision::PlaneX3D plane(10);
		collision::Box2D box(Vec2d(0, 0), Vec2d(10, 10));

		collision::Surface3D surface(std::make_unique<collision::PlaneX3D>(10), std::make_unique<collision::Box2D>(box));

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

	void ShapeGeneratingTest()
	{
		using namespace accord;
		using namespace accord::shape;

		Random::SetSeed();

		auto a = generating::CreatePlane(5, Axis3D::x);


		generating::Box3D b1({ 0, 0, 0 }, { 10, 10, 10 });
		for (int i = 0; i < 10; i++)
		{
			LOG_DEBUG(b1.GeneratePointOnSurface());
		}
	}

	void ShapeRelationTest()
	{
		using namespace accord;
		using namespace accord::shape;

		Random::SetSeed();
		relation::Box2D b1({ 0, 0 }, { 10, 10 });
		relation::Box2D b2({ 5, 5 }, { 10, 10 });
		relation::Box2D b3({ -5, -5 }, { 20, 20 });

		relation::Circle c1({ 5, 5 }, 1);
		relation::Circle c2({ 5, 5 }, 5 * std::sqrt(2));
		relation::Circle c3({ 5, 5 }, 5.01 * std::sqrt(2));
		relation::Circle c4({ -5, 5 }, 1);

		relation::Surface3DShape& s1 = b1;
		relation::Surface3DShape& s2 = b2;
		relation::Surface3DShape& s3 = b3;


		LOG_DEBUG(c1.IsOverlapping(b1)); // true
		LOG_DEBUG(b1.IsOverlapping(c1)); // true
		LOG_DEBUG(c4.IsOverlapping(b1)); // false
		LOG_DEBUG(c1.IsEnvelopedBy(b1)); // true
		LOG_DEBUG(c2.IsEnvelopedBy(b1)); // false // circle exact radius to envelop box does not envelop it. 
		LOG_DEBUG(c3.IsEnvelopedBy(b1)); // false // circle needs to be slightly bigger
		LOG_DEBUG(c3.IsEnveloping(b1)); // true

		LOG_DEBUG(b1.IsOverlapping(b2));
		LOG_DEBUG(b2.IsOverlapping(b1));
		LOG_DEBUG(b3.IsEnveloping(b1));
		LOG_DEBUG(b1.IsEnveloping(b3));

		LOG_DEBUG(s1.IsOverlapping(s2));
		LOG_DEBUG(s2.IsOverlapping(s1));
		LOG_DEBUG(s3.IsEnveloping(s1));
		LOG_DEBUG(s1.IsEnveloping(s3));

		relation::Box3D box3d1({ 0, 0, 0 }, { 10, 10, 10 });

		relation::Box3D box3d2({ 10, 2, 0 }, { 10, 10, 10 });

		auto face = box3d1.IsPartiallyNeighbouring(box3d2);
		if (face.has_value())
		{
			LOG_DEBUG("neighbouring face = {}", face.value());
		}
		else
		{
			LOG_DEBUG("no neighbour");
		}
		
		


		relation::Box3D bx1({ 0, 0, 0 }, { 10, 10, 10 });
		relation::Box3D bx2({ 4, 5, 6 }, { 10, 10, 10 });
		LOG_DEBUG(JsonToPrettyString(bx1.GenerateOverlapBox(bx2)));

	}
}