#include "pch.h"
#include "basic_circle.h"
#include "constants.h"

namespace accord::shape::basic
{
	Circle::Circle(Vec2d centre, double radius)
		: centre(centre), radius(radius)
	{

	}

	void Circle::Move(const Vec2d& centre)
	{
		this->centre = centre;
	}

	void Circle::Resize(const double radius)
	{
		this->radius = radius;
	}

	const Vec2d& Circle::GetCentre() const
	{
		return centre;
	}

	const double& Circle::GetRadius() const
	{
		return radius;
	}

	double Circle::CalculateArea() const
	{
		return PI * radius * radius;
	}

	void Circle::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Circle& circle)
	{
		j["centre"] = circle.GetCentre();
		j["radius"] = circle.GetRadius();
	}
}