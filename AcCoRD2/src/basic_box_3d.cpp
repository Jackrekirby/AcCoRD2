#include "pch.h"
#include "box_3d.h"

namespace accord::shape::basic
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: origin(origin), length(length), end(origin + length)
	{

	}

	void Box3D::Move(const Vec3d& origin)
	{
		this->origin = origin;
		this->end = origin + length;
	}

	void Box3D::Resize(const Vec3d& length)
	{
		this->length = length;
		this->end = origin + length;
	}

	const Vec3d& Box3D::GetOrigin() const
	{
		return origin;
	}

	const Vec3d& Box3D::GetEnd() const
	{
		return end;
	}

	const Vec3d& Box3D::GetLength() const
	{
		return length;
	}

	void to_json(Json& j, const Box3D& box)
	{
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
	}
}