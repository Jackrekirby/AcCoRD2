#include "pch.h"
#include "collision_cylinder.h"
#include "vec1d.h"
#include "vec3d.h"
#include "axis_3d.h"

namespace accord::shape::collision
{
	Cylinder::Cylinder(const Vec3d& base_centre, double radius, double length, const Axis3D& axis)
		: basic::Cylinder(base_centre, radius, length, axis),
		circle(GetCircleCentre(), radius),
		base_face({ GetBase(), axis }, { GetCircleCentre(), radius }),
		top_face({ GetTop(), axis }, { GetCircleCentre(), radius })
	{

	}

	std::optional<Collision3D> Cylinder::CalculateExternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const
	{
		// check path collision with tube first
		std::optional<Collision2D> collision2D =
			circle.CalculateExternalCollisionData(origin.GetPlane(GetAxis()), end.GetPlane(GetAxis()));
		// if path collided with tube must check if it was between the base and top faces
		// if the path was not between the faces it may have hit a face
		if (collision2D.has_value())
		{
			double longitudinal_intersection =
				Vec1d::Lerp(origin.GetAxis(GetAxis()), end.GetAxis(GetAxis()), collision2D->time);
			if (longitudinal_intersection >= GetBase() && longitudinal_intersection <= GetTop())
			{
				double longitudinal_reflection = end.GetAxis(GetAxis());
				Vec3d intersection = { longitudinal_intersection, collision2D->intersection , GetAxis() };
				Vec3d reflection = { longitudinal_reflection, collision2D->reflection , GetAxis() };
				return Collision3D(collision2D->time, intersection, reflection);
			}
		}
		std::optional<Collision3D> collision3D;
		collision3D = base_face.CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision3D.has_value()) { LOG_DEBUG("base");  return collision3D; }
		collision3D = top_face.CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision3D.has_value()) { LOG_DEBUG("top"); }
		return collision3D;
	}

	std::optional<Collision3D> Cylinder::CalculateInternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const
	{
		// check path collision with tube first
		std::optional<Collision2D> collision2D =
			circle.CalculateInternalCollisionData(origin.GetPlane(GetAxis()), end.GetPlane(GetAxis()));
		// if path collided with tube must check if it was between the base and top faces
		// if the path was not between the faces it may have hit a face
		if (collision2D.has_value())
		{
			double longitudinal_intersection =
				Vec1d::Lerp(origin.GetAxis(GetAxis()), end.GetAxis(GetAxis()), collision2D->time);
			if (longitudinal_intersection >= GetBase() && longitudinal_intersection <= GetTop())
			{
				double longitudinal_reflection = end.GetAxis(GetAxis());
				Vec3d intersection = { longitudinal_intersection, collision2D->intersection , GetAxis() };
				Vec3d reflection = { longitudinal_reflection, collision2D->reflection , GetAxis() };
				return Collision3D(collision2D->time, intersection, reflection);
			}
		}
		std::optional<Collision3D> collision3D;
		collision3D = base_face.CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision3D.has_value()) { LOG_DEBUG("base");  return collision3D; }
		collision3D = top_face.CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision3D.has_value()) { LOG_DEBUG("top"); }
		return collision3D;
	}

	void Cylinder::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Cylinder& cylinder)
	{
		j = static_cast<basic::Cylinder>(cylinder);
	}
}