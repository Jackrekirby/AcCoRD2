#pragma once
//#include <optional>
//#include "json.h"
#include "basic_plane.h"

namespace accord::shape::collision
{
	class Plane1D
	{
	public:
		std::optional<double> CalculateCollisionTimeWithPositiveFace(double origin, double end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(double origin, double end) const;

		virtual const double& GetPosition() const = 0;
	};
}