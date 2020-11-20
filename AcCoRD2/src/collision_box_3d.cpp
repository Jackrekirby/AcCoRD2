#include "pch.h"
#include "collision_box_3d.h"
#include "collision_surface_3d_factory.h"
#include "vec3b.h"

namespace accord::shape::collision
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length), faces(GenerateFaces())
	{

	}

	std::enum_array<Face, Surface3D, 6> Box3D::GenerateFaces() const
	{
		return
		{
			CreateBoxSurface(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::z, GetOrigin(), GetEnd()),
		};
	}

	std::optional<Collision3D> Box3D::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end)
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

	std::optional<Collision3D> Box3D::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end)
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

	const std::enum_array<Face, Surface3D, 6>& Box3D::GetFaces() const
	{
		return faces;
	}

	void to_json(Json& j, const Box3D& box)
	{
		j = static_cast<basic::Box3D>(box);
		j["faces"] = box.GetFaces();
	}
}