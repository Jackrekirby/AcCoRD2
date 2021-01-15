#include "pch.h"
#include "collision_plane_1d.h"

namespace accord::shape::collision
{
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
}