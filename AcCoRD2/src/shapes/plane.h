#pragma once
#include <optional>
#include "json.h"

namespace accord::shapes
{
	class Plane
	{
	public:
		Plane(double position);

		std::optional<double> CalculateCollisionTimeWithPositiveFace(double origin, double end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(double origin, double end) const;

		const double& GetPosition() const;
	protected:
	
		double position;
	};

	void to_json(Json& j, const Plane& plane);
}