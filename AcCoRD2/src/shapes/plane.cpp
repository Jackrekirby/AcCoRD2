#include "plane.h"

namespace accord::shapes
{
	Plane::Plane(double position)
		: position(position)
	{

	}

	const double& Plane::GetPosition() const
	{
		return position;
	}

	void to_json(Json& j, const Plane& plane)
	{
		j["position"] = plane.GetPosition();
	}

	std::optional<double> Plane::CalculateCollisionTimeWithPositiveFace(double origin, double end) const
	{
		if (origin >= position && end < position)
		{
			return (position - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}

	std::optional<double> Plane::CalculateCollisionTimeWithNegativeFace(double origin, double end) const
	{
		if (origin <= position && end > position)
		{
			return (position - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}
}