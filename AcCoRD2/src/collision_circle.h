#pragma once
#include "collision_2d.h"
#include "basic_circle.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	class Circle : public basic::Circle, public Shape2D
	{
	public:
		Circle(Vec2d centre, double radius);

		std::optional<Collision2D> CalculateExternalCollisionData(const Vec2d& origin, const Vec2d& end) const;

		std::optional<Collision2D> CalculateInternalCollisionData(const Vec2d& origin, const Vec2d& end) const;

		bool IsWithinOrOnBorder(const Vec2d& position) const;

		void ToJson(Json& j) const;

	private:
		struct CollisionTimes
		{
			double t1, t2;

			CollisionTimes(double t1, double t2);
		};

		std::optional<CollisionTimes> CalculateCollisionTime(const Vec2d& origin, const Vec2d& end) const;

		std::optional<double> SelectExternalCollisionTime(double t1, double t2) const;

		std::optional<double> SelectInternalCollisionTime(double t1, double t2) const;
	};

	void to_json(Json& j, const Circle& circle);
}
