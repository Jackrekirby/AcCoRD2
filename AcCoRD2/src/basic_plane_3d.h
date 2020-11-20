#pragma once
#include "axis_3d.h"

namespace accord::shape::basic
{
	class AbstractPlane3D
	{
	public:
		AbstractPlane3D(double position, Axis3D axis);

		const Axis3D& GetAxis() const;

		const double& GetPosition() const;
	private:
		double position;
		Axis3D axis;
	};

	void to_json(Json& j, const AbstractPlane3D& plane);
}
