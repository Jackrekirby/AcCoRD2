#include "pch.h"
#include "shape_test.h"

#include "collision_surface.h"
#include "collision_rect.h"
#include "collision_plane.h"
#include "collision_3d.h"
#include "collision_box.h"
#include "collision_sphere.h"

#include "generating_plane.h"
#include "generating_surface.h"
#include "generating_rect.h"
#include "generating_box.h"

#include "relation_box.h"
#include "relation_rect.h"
#include "relation_circle.h"
#include "relation_rect_surface.h"
#include "relation_plane.h"
#include "relation_sphere.h"

namespace accord
{
	void ShapeCollisionTest()
	{
		using namespace accord::shape;
		using namespace accord;

		//collision::PlaneX plane(10);
		//collision::Rect box(Vec2d(0, 0), Vec2d(10, 10));

		//collision::Surface surface(std::make_unique<collision::PlaneX>(10), std::make_unique<collision::Rect>(box));

		accord::Vec3d origin(11, 0, 0);
		accord::Vec3d end(13, 0, 0);
		///accord::Vec3d end(-1.5, 0, 0);

		LOG_INFO("origin = {}, end = {}", origin, end);
		collision::Sphere sphere({ 0, 0, 0 }, 10);

		LOG_INFO(sphere.CalculateInternalCollisionData(origin, end));

		//LOG_INFO(surface.CalculateCollisionDataWithNegativeFace(origin, end));

		//Box box3d(Vec3d(-1, -1, -1), Vec3d(2, 2, 2));
		//collision::Box box3d(Vec3d(0, 0, 0), Vec3d(10, 10, 10));

		//LOG_INFO(box3d.CalculateInternalCollisionData(origin, end));
		//LOG_INFO(box3d.CalculateExternalCollisionData(origin, end));
		//accord::Json j;
		//j = box3d;

		//LOG_INFO(accord::JsonToPrettyString(j));
	}

	void ShapeGeneratingTest()
	{
		using namespace accord;
		using namespace accord::shape;

		Random::SetSeed();

		generating::Plane a(5, Axis3D::x);


		generating::Box b1({ 0, 0, 0 }, { 10, 10, 10 });
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
		relation::Rect b1({ 0, 0 }, { 10, 10 });
		relation::Rect b2({ 5, 5 }, { 10, 10 });
		relation::Rect b3({ -5, -5 }, { 20, 20 });

		relation::Circle c1({ 5, 5 }, 1);
		relation::Circle c2({ 5, 5 }, 5 * std::sqrt(2));
		relation::Circle c3({ 5, 5 }, 5.01 * std::sqrt(2));
		relation::Circle c4({ -5, 5 }, 1);

		relation::Shape2D& s1 = b1;
		relation::Shape2D& s2 = b2;
		relation::Shape2D& s3 = b3;


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

		relation::Box box3d1({ 0, 0, 0 }, { 10, 10, 10 });

		relation::Box box3d2({ 10, 2, 0 }, { 10, 10, 10 });

		bool face = box3d1.IsPartiallyNeighbouring(box3d2);
		if (face)
		{
			LOG_DEBUG("neighbouring face");
		}
		else
		{
			LOG_DEBUG("no neighbour");
		}
		
		


		relation::Box bx1({ 0, 0, 0 }, { 10, 10, 10 });
		relation::Box bx2({ 4, 5, 6 }, { 10, 10, 10 });
		LOG_DEBUG(JsonToPrettyString(bx1.GenerateOverlapBox(bx2)));






	}


	std::string IsFalse(bool b)
	{
		return b ? "WRONG" : "CORRECT";
	}


	void Shape3DRelationTest()
	{
		using namespace accord;
		using namespace accord::shape;

		relation::Sphere s1({ 0, 0, 0 }, 20);

		relation::Box b1({ -5, -5, -5 }, {10, 10, 10});

		//relation::Shape3D& h1 = s1;
		//relation::Shape3D& h2 = b1;

		//LOG_INFO(accord::JsonToPrettyString(j));

		//LOG_INFO("sphere : {} \n box : {}",  ((Json)(h1)).dump(true), ((Json)(h2)).dump(true));
		//assert(s1.IsEnveloping(b1) == false);


		//LOG_INFO(s1.IsEnvelopedBy(b1));
		//LOG_INFO(s1.IsOverlapping(b1));

		//Json j = h1;
		//LOG_DEBUG(j.dump(-1, ' '));


		//std::string a = fmt::format("hello {}", 5);

		//basic::Box b2({ 1, 2, 3 }, { 4, 5, 6 });

		//LOG_INFO(h1);


	}
}