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
		// see https://en.wikipedia.org/wiki/Line–sphere_intersection
		// nabla operator = n
		// t = collision time where t = 0 is at origin and t = 1 is at end position
		
		const Vec3d& o = origin;
		const Vec3d& c = GetCentre();
		const double& r = GetRadius();
		Vec3d d = o - c;
		Vec3d u = (end - origin).Normalise();
		
		double ud = Vec3d::DotProduct(u, d);
		double n = Square(ud) - (d.Size2() - Square(r));

		if (n <= 0) return std::nullopt;

		double sqrt_n = std::sqrt(n);
		double oe = (end - origin).Size();
		double t1 = (-ud + sqrt_n) / oe;
		double t2 = (-ud - sqrt_n) / oe;

		std::optional<double> t = SelectCorrectCollisionTime(t1, t2);
		if (~t.has_value()) return std::nullopt;
		double time = t.value();

		// Calculate intersection and reflected points
		Vec3d intersection = Vec3d::Lerp(origin, end, time);
		Vec3d reflection = (end - intersection).Reflect((intersection - c).Normalise()) + intersection;

		return Collision3D(time, intersection, reflection);
	}

	std::optional<double> SelectCorrectCollisionTime(double t1, double t2)
	{
		// Molecule in inside circle (which it shouldn't be, but can be a result of floating point error)
		if (t1 * t2 < 0) 
		{
			// molecule is inside sphere and moving towards the centre [reflection required]
			if (t1 < 0 && -t1 < t2) 
			{
				return t1;
			} if (t1 < 0 && -t1 < t2)
			{
				return t2;
			}
			// molecule is inside sphere and moving away the centre [let it leave]
			return std::nullopt;
		}
		// molecule is outside of sphere and moving away from sphere [let the molecule continue]
		else if (t1 <= 0 && t2 <= 0) 
		{
			// must be checked before next if statement
			return std::nullopt;
		}
		else
		{
			// Molecule is outside of circle at origin and heading towards the sphere.
			
			// Get the closest time and if it is before the end a [reflection is required]
			if (t1 <= t2 && t1 < 1.0) 
			{
				return t1;
			}
			else if (t2 < t1 && t2 < 1.0)
			{
				return t2;
			}
			// If the closest time is after the end then [let the molecule continue]
			return std::nullopt;
		}
	}

	std::optional<Collision3D> Sphere::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end)
	{
		return std::nullopt;
	}

	bool Sphere::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return ((position - GetCentre()).Size() < GetRadius());
	}
	

	void to_json(Json& j, const Sphere& sphere)
	{
		j = static_cast<basic::Sphere>(sphere);
	}
}
