#include "pch.h"
#include "basic_box.h"
#include "vec3b.h"

namespace accord::shape::basic
{
	Box::Box(Vec3d origin, Vec3d length)
		: origin(origin), length(length), end(origin + length)
	{

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
		return ((position == GetOrigin()) || (position == GetEnd())).All();
	}

	void to_json(Json& j, const Box& box)
	{
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
	}
}