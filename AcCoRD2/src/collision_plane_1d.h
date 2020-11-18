#pragma once
//#include <optional>
//#include "json.h"
#include "pch.h"
#include "basic_plane_3d.h"

namespace accord::shape::collision
{
	class Plane1D : public basic::AbstractPlane3D
	{
	public:
		Plane1D(double position, Axis3D axis);

		std::optional<double> CalculateCollisionTimeWithPositiveFace(double origin, double end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(double origin, double end) const;
	};

	void to_json(Json& j, const Plane1D& plane);
}