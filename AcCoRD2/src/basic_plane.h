#pragma once
#include "axis_3d.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	class Plane : public Shape
	{
	public:
		// constructs position of plane along the dimension specified.
		// the plane lies perpendicular to the specified axis
		Plane(double position, Axis3D axis);

		const Axis3D& GetAxis() const;

		const double& GetPosition() const;

		void ToJson(Json& j) const;

		// log plane to output stream
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Plane& plane)
		{
			return os << fmt::format("position = {}, axis = {}",
				plane.GetPosition(), plane.GetAxis());
		}
	private:
		double position;
		Axis3D axis;
	};

	void to_json(Json& j, const Plane& plane);
}
