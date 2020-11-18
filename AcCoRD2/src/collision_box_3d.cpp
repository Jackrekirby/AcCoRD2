#include "pch.h"
#include "collision_box_3d.h"
#include "vec3b.h"
#include "collision_plane_x_3d.h"
#include "collision_plane_y_3d.h"
#include "collision_plane_z_3d.h"
#include "collision_box_2d.h"

namespace accord::shape::collision
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length),
		faces { Surface3D(std::make_unique<PlaneX_3D>(GetOrigin().x), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::x), GetEnd().GetPlane(Axis3D::x))),
				Surface3D(std::make_unique<PlaneY_3D>(GetOrigin().y), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::y), GetEnd().GetPlane(Axis3D::y))),
				Surface3D(std::make_unique<PlaneZ_3D>(GetOrigin().z), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::z), GetEnd().GetPlane(Axis3D::z))),
				Surface3D(std::make_unique<PlaneX_3D>(GetEnd().x), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::x), GetEnd().GetPlane(Axis3D::x))),
				Surface3D(std::make_unique<PlaneY_3D>(GetEnd().y), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::y), GetEnd().GetPlane(Axis3D::y))),
				Surface3D(std::make_unique<PlaneZ_3D>(GetEnd().z), std::make_unique<collision::Box2D>(GetOrigin().GetPlane(Axis3D::z), GetEnd().GetPlane(Axis3D::z))) }
	{

	}

	std::optional<Collision3D> Box3D::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Faces::nx).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nx"); return collision; }
		collision = faces.at(Faces::ny).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("ny"); return collision; }
		collision = faces.at(Faces::nz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nz"); return collision; }
		collision = faces.at(Faces::px).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("px"); return collision; }
		collision = faces.at(Faces::py).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("py"); return collision; }
		collision = faces.at(Faces::pz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("pz"); }
		return collision;
	}

	std::optional<Collision3D> Box3D::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Faces::nx).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nx");  return collision; }
		collision = faces.at(Faces::ny).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("ny"); return collision; }
		collision = faces.at(Faces::nz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nz"); return collision; }
		collision = faces.at(Faces::px).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("px"); return collision; }
		collision = faces.at(Faces::py).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("py"); return collision; }
		collision = faces.at(Faces::pz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("pz"); }
		return collision;
	}

	bool Box3D::IsWithinBorder(const Vec3d& position) const
	{
		return ((position > GetOrigin()).All() && (position < GetEnd()).All());
	}

	bool Box3D::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return ((position >= GetOrigin()).All() && (position <= GetEnd()).All());
	}

	bool Box3D::IsOnBorder(const Vec3d& position) const
	{
		return ((position == GetOrigin()) || (position == GetEnd())).All();
	}

	void to_json(Json& j, const Box3D& box)
	{
		j = static_cast<basic::Box3D>(box);
		j["faces"] = box.GetFaces();
	}
}