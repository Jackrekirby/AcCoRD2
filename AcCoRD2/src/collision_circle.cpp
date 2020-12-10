#pragma once
#include "pch.h"
#include "collision_circle.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	Circle::Circle(Vec2d centre, double radius)
		: basic::Circle(centre, radius)
	{

	}

	bool Circle::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return basic::Circle::IsWithinOrOnBorder(position);
	}

	std::optional<Collision2D> Circle::CalculateExternalCollisionData(const Vec2d& origin, const Vec2d& end) const
	{
		// find the collision times of the line (formed by points origin and end) with the sphere
		std::optional<CollisionTimes> ct = CalculateCollisionTime(origin, end);
		if (!ct.has_value()) return std::nullopt;

		LOG_TRACE("t1 = {}, t2 = {}", ct->t1, ct->t2);
		//check to see which collision point is the valid one if any
		std::optional<double> time = SelectExternalCollisionTime(ct->t1, ct->t2);
		if (!time.has_value()) return std::nullopt;

		// Calculate intersection and reflected points
		Vec2d intersection = Vec2d::Lerp(origin, end, *time);
		Vec2d reflection = (end - intersection).Reflect((intersection - GetCentre()).Normalise()) + intersection;

		return Collision2D(*time, intersection, reflection);
	}

	std::optional<Collision2D> Circle::CalculateInternalCollisionData(const Vec2d& origin, const Vec2d& end) const
	{
		// find the collision times of the line (formed by points origin and end) with the sphere
		std::optional<CollisionTimes> ct = CalculateCollisionTime(origin, end);
		if (!ct.has_value()) return std::nullopt;

		LOG_TRACE("t1 = {}, t2 = {}", ct->t1, ct->t2);
		//check to see which collision point is the valid one if any
		std::optional<double> time = SelectInternalCollisionTime(ct->t1, ct->t2);
		if (!time.has_value()) return std::nullopt;

		// Calculate intersection and reflected points
		Vec2d intersection = Vec2d::Lerp(origin, end, *time);
		Vec2d reflection = (end - intersection).Reflect((intersection - GetCentre()).Normalise()) + intersection;

		return Collision2D(*time, intersection, reflection);
	}

	Circle::CollisionTimes::CollisionTimes(double t1, double t2)
		: t1(t1), t2(t2)
	{

	}

	std::optional<Circle::CollisionTimes> Circle::CalculateCollisionTime(const Vec2d& origin, const Vec2d& end) const
	{
		Vec2d direction = end - origin;
		Vec2d relative_origin = origin - GetCentre();
		// find where the line (formed by points origin and end) and circle intersection using quadratic formula 
		double a = Vec2d::DotProduct(direction, direction);
		double b = 2 * Vec2d::DotProduct(relative_origin, direction);
		double c = Vec2d::DotProduct(relative_origin, relative_origin) - GetRadius2();

		double discriminant = b * b - 4 * a * c;
		if (discriminant <= 0) return std::nullopt;

		// Solutions of quadratic formula calculates the intersection times
		// Quadratic formula used optimised for computer use to reduce floating point error.
		double q = (b > 0) ? -0.5 * (b + std::sqrt(discriminant)) : -0.5 * (b - std::sqrt(discriminant));
		double time_a = q / a, time_b = c / q;
		return CollisionTimes(q / a, c / q);
	}

	std::optional<double> Circle::SelectExternalCollisionTime(double t1, double t2) const
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

	std::optional<double> Circle::SelectInternalCollisionTime(double t1, double t2) const
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
	
	void Circle::ToJson(Json& j) const
	{
		j = static_cast<basic::Circle>(*this);
	}

	void to_json(Json& j, const Circle& circle)
	{
		circle.ToJson(j);
	}
}
