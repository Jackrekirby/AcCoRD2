#pragma once
#include "vec2d.h"

namespace accord::shape::basic
{
	class Circle
	{
	public:
		Circle(Vec2d centre, double radius);

		void Move(const Vec2d& centre);

		void Resize(double radius);

		const Vec2d& GetCentre() const;

		const double& GetRadius() const;

		double CalculateArea() const;
		
		void ToJson(Json& j) const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Circle& circle)
		{
			return os << fmt::format("centre = {}, radius = {}",
				circle.GetCentre(), circle.GetRadius());
		}

	private:
		Vec2d centre;
		double radius;
	};

	void to_json(Json& j, const Circle& circle);
}