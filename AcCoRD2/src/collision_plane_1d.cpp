#include "collision_plane_1d.h"

namespace accord::shape::collision
{
	Plane1D::Plane1D(double position, Axis3D axis)
		: basic::AbstractPlane3D(position, axis)
	{

	}

	std::optional<double> Plane1D::CalculateCollisionTimeWithPositiveFace(double origin, double end) const
	{
		if (origin >= GetPosition() && end < GetPosition())
		{
			return (GetPosition() - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}

	std::optional<double> Plane1D::CalculateCollisionTimeWithNegativeFace(double origin, double end) const
	{
		if (origin <= GetPosition() && end > GetPosition())
		{
			return (GetPosition() - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}

	void to_json(Json& j, const Plane1D& plane)
	{
		j = static_cast<basic::AbstractPlane3D>(plane);
	}
}