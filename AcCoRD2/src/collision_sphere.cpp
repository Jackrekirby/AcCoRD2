#include "pch.h"
#include "collision_sphere.h"
#include "vec3d.h"
#include "vec3b.h"
#include "vec1d.h"

namespace accord::shape::collision
{

	Sphere::Sphere(Vec3d centre, double radius)
		: basic::Sphere(centre, radius)
	{

	}

	std::optional<Collision3D> Sphere::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		// find the collision times of the line (formed by points origin and end) with the sphere
		std::optional<CollisionTimes> ct = CalculateCollisionTime(origin, end);
		if (!ct.has_value()) return std::nullopt;

		LOG_TRACE("t1 = {}, t2 = {}", ct->t1, ct->t2);
		//check to see which collision point is the valid one if any
		std::optional<double> time = SelectExternalCollisionTime(ct->t1, ct->t2);
		if (!time.has_value()) return std::nullopt;

		// Calculate intersection and reflected points
		Vec3d intersection = Vec3d::Lerp(origin, end, *time);
		Vec3d reflection = (end - intersection).Reflect((intersection - GetCentre()).Normalise()) + intersection;

		return Collision3D(*time, intersection, reflection);
	}

	std::optional<Collision3D> Sphere::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		// find the collision times of the line (formed by points origin and end) with the sphere
		std::optional<CollisionTimes> ct = CalculateCollisionTime(origin, end);
		if (!ct.has_value()) return std::nullopt;

		LOG_TRACE("t1 = {}, t2 = {}", ct->t1, ct->t2);
		//check to see which collision point is the valid one if any
		std::optional<double> time = SelectInternalCollisionTime(ct->t1, ct->t2);
		if (!time.has_value()) return std::nullopt;

		// Calculate intersection and reflected points
		Vec3d intersection = Vec3d::Lerp(origin, end, *time);
		Vec3d reflection = (end - intersection).Reflect((intersection - GetCentre()).Normalise()) + intersection;

		return Collision3D(*time, intersection, reflection);
	}

	Sphere::CollisionTimes::CollisionTimes(double t1, double t2)
		: t1(t1), t2(t2)
	{

	}

	std::optional<Sphere::CollisionTimes> Sphere::CalculateCollisionTime(const Vec3d& origin, const Vec3d& end)
	{
		// see https://en.wikipedia.org/wiki/Line–sphere_intersection
		// nabla operator = n
		// t = collision time where t = 0 is at origin and t = 1 is at end position

		Vec3d oc = origin - GetCentre();
		double a = Vec3d::DotProduct((end - origin).Normalise(), oc);
		double n = Vec1d::Square(a) - (oc.Size2() - GetRadius2());

		LOG_TRACE("n = {}", n);
		if (n <= 0) return std::nullopt;

		double sqrt_n = std::sqrt(n);
		double oe = (end - origin).Size();
		return CollisionTimes((-a + sqrt_n) / oe, (-a - sqrt_n) / oe);
	}

	std::optional<double> Sphere::SelectExternalCollisionTime(double t1, double t2)
	{
		// Molecule in inside circle (which it shouldn't be, but can be a result of floating point error)
		if (t1 * t2 < 0)
		{
			LOG_TRACE("inside sphere");
			// molecule is inside sphere and moving towards the centre [reflection required]
			if (t1 < 0 && -t1 < t2) return t1;
			if (t2 < 0 && -t2 < t1) return t2;
			// molecule is inside sphere and moving away the centre [let it leave]
			return std::nullopt;
		}
		// molecule is outside of sphere and moving away from sphere [let the molecule continue]
		else if (t1 <= 0 && t2 <= 0)
		{
			LOG_TRACE("outside sphere and moving away from sphere");
			// must be checked before next if statement
			return std::nullopt;
		}
		else
		{
			// Molecule is outside of circle at origin and heading towards the sphere.
			LOG_TRACE("outside sphere and moving towards sphere");
			// Get the closest time and if it is before the end a [reflection is required]
			if (t1 <= t2 && t1 < 1.0) return t1;
			if (t2 < t1 && t2 < 1.0) return t2;
			// If the closest time is after the end then [let the molecule continue]
			return std::nullopt;
		}
	}

	std::optional<double> Sphere::SelectInternalCollisionTime(double t1, double t2)
	{
		if (t1 > t2)
		{
			if (t1 < 1.0) return t1;
		}
		else
		{
			if (t2 < 1.0) return t2;
		}
		return std::nullopt;
	}

	void to_json(Json& j, const Sphere& sphere)
	{
		j = static_cast<basic::Sphere>(sphere);
	}
}
