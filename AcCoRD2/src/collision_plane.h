#pragma once
#include "pch.h"
#include "basic_plane.h"
#include "vec3d.h"

namespace accord::shape::collision
{
	// collision plane checks if a ray crosses a plane
	// used to construct collision surfaces, used by collision boxes and cylinders
	class Plane : public basic::Plane
	{
	public:
		// define the plane either with primitive parameters or a basic plane
		Plane(double position, const Axis3D& axis);

		Plane(basic::Plane plane);

		// calculate if a ray crosses a plane from the POSITIVE to NEGATIVE side
		// if the ray does cross the plane it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		// the 3D collision can be simplified to a 1D collsion
		std::optional<double> CalculateCollisionTimeWithPositiveFace(double origin, double end) const;

		// calculate if a ray crosses a plane from the NEGATIVE to POSITIVE side
		// if the ray does cross the plane it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		// the 3D collision can be simplified to a 1D collsion
		std::optional<double> CalculateCollisionTimeWithNegativeFace(double origin, double end) const;

		// calculate if a ray cross a plane from the POSITIVE to NEGATIVE side
		// if the ray does cross the plane it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		std::optional<double> CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		// calculate if a ray cross a plane from the NEGATIVE to POSITIVE side
		// if the ray does cross the plane it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		std::optional<double> CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		// calculate intersection point by linearly interpolating between ray start and end position
		Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const;

		// calculate the reflection of the ray from an intersection point
		Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const;
	};

	void to_json(Json& j, const Plane& plane);
}
