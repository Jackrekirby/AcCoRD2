#include "pch.h"
#include "basic_box.h"

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

	double Box::CalculateVolume() const
	{
		return length.Volume();
	}

	void to_json(Json& j, const Box& box)
	{
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
	}
}