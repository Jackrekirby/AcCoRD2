#include "pch.h"
#include "collision_box.h"
#include "collision_rect_surface.h"
#include "collision_plane_factory.h"

namespace accord::shape::collision
{
	Box::Box(Vec3d origin, Vec3d length)
		: basic::Box(origin, length), faces(GenerateFaces())
	{

	}

	std::enum_array<Face, RectSurface, 6> Box::GenerateFaces() const
	{
		return
		{
			GenerateFace(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::z, GetOrigin(), GetEnd())
		};
	}

	RectSurface Box::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const
	{
		return { CreatePlane(position.GetAxis(axis), axis), { origin.GetPlane(axis), end.GetPlane(axis) } };
	}

	std::optional<Collision3D> Box::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Face::nx).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nx"); return collision; }
		collision = faces.at(Face::ny).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("ny"); return collision; }
		collision = faces.at(Face::nz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nz"); return collision; }
		collision = faces.at(Face::px).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("px"); return collision; }
		collision = faces.at(Face::py).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("py"); return collision; }
		collision = faces.at(Face::pz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("pz"); }
		return collision;
	}

	std::optional<Collision3D> Box::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Face::nx).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nx");  return collision; }
		collision = faces.at(Face::ny).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("ny"); return collision; }
		collision = faces.at(Face::nz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("nz"); return collision; }
		collision = faces.at(Face::px).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("px"); return collision; }
		collision = faces.at(Face::py).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("py"); return collision; }
		collision = faces.at(Face::pz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { LOG_DEBUG("pz"); }
		return collision;
	}

	const std::enum_array<Face, RectSurface, 6>& Box::GetFaces() const
	{
		return faces;
	}

	void Box::ToJson(Json& j) const
	{
		j = static_cast<basic::Box>(*this);
		j["faces"] = GetFaces();
	}

	void to_json(Json& j, const Box& box)
	{
		box.ToJson(j);
	}
}