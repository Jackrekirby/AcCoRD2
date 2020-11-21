#pragma once
#include "axis_3d.h"

namespace accord::shape::basic
{
	class AbstractPlane
	{
	public:
		AbstractPlane(double position, Axis3D axis);

		const Axis3D& GetAxis() const;

		const double& GetPosition() const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const AbstractPlane& plane)
		{
			return os << fmt::format("position = {}, axis = {}",
				plane.GetPosition(), plane.GetAxis());
		}
	private:
		double position;
		Axis3D axis;
	};

	void to_json(Json& j, const AbstractPlane& plane);
}
