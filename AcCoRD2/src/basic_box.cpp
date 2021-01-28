#include "pch.h"
#include "basic_box.h"
#include "vec3b.h"
#include "vec2d.h"
#include "basic_cylinder.h"
#include "basic_sphere.h"
#include "basic_rect_surface.h"

namespace accord::shape::basic
{
	Box::Box(Vec3d origin, Vec3d length)
		: origin(origin), length(length), end(origin + length)
	{

	}

	Box::Box(const Cylinder& cylinder)
		: origin(cylinder.GetBase(), cylinder.GetCircleCentre() - cylinder.GetRadius(), cylinder.GetAxis()),
		length(cylinder.GetLength(), { 2 * cylinder.GetRadius(), 2 * cylinder.GetRadius() }, cylinder.GetAxis()),
		end(origin + length)
	{
	}

	Box::Box(const Sphere& sphere)
		: origin(sphere.GetCentre() - sphere.GetRadius()),
		length(sphere.GetRadius() * 2),
		end(origin + length)
	{

	}

	Box::Box(const RectSurface& rect_surface)
		:origin(Vec3d(0, rect_surface.rect.GetOrigin(), rect_surface.plane.GetAxis())),
		length(Vec3d(0, rect_surface.rect.GetLength(), rect_surface.plane.GetAxis()))
	{

	}

	Box Box::GenerateBoundingBox() const
	{
		return *this;
	}

	Box Box::GenerateBoundingBox(const Box& box) const
	{
		return {Vec3d::Min(origin, box.origin), Vec3d::Max(end, box.end) - Vec3d::Min(origin, box.origin) };
	}

	void Box::Move(const Vec3d& origin)
	{
		this->origin = origin;
		this->end = origin + length;
	}

	void Box::Resize(const Vec3d& length)
	{
		this->length = length;
		this->end = origin + length;
	}

	const Vec3d& Box::GetOrigin() const
	{
		return origin;
	}

	const Vec3d& Box::GetEnd() const
	{
		return end;
	}

	const Vec3d& Box::GetLength() const
	{
		return length;
	}

	Vec3d Box::CalculateCentre() const
	{
		return origin + 0.5 * length;
	}

	double Box::CalculateVolume() const
	{
		return length.Volume();
	}

	double Box::CalculateSurfaceArea() const
	{
		return ((2 * length.x * length.y) + (2 * length.y * length.z) + (2 * length.x * length.z));
	}

	void Box::ToJson(Json& j) const
	{
		j = *this;
	}

	bool Box::IsWithinBorder(const Vec3d& position) const
	{
		return ((position > GetOrigin()).All() && (position < GetEnd()).All());
	}

	bool Box::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return ((position >= GetOrigin()).All() && (position <= GetEnd()).All());
	}

	bool Box::IsOnBorder(const Vec3d& position) const
	{
		//LOG_INFO("{} {} {}", position, GetOrigin(), GetEnd());
		return (IsWithinOrOnBorder(position) && ((position == GetOrigin()) || (position == GetEnd())).Any());
	}

	void to_json(Json& j, const Box& box)
	{
		j["type"] = "box";
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
	}
}