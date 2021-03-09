// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "basic_circle.h"
#include "constants.h"

namespace accord::shape::basic
{
	Circle::Circle(Vec2d centre, double radius)
		: centre(centre), radius(radius), radius2(radius*radius)
	{

	}

	void Circle::Move(const Vec2d& centre)
	{
		this->centre = centre;
	}

	void Circle::Resize(const double radius)
	{
		this->radius = radius;
		radius2 = radius * radius;
	}

	const Vec2d& Circle::GetCentre() const
	{
		return centre;
	}

	const double& Circle::GetRadius() const
	{
		return radius;
	}

	const double& Circle::GetRadius2() const
	{
		return radius2;
	}

	double Circle::CalculateArea() const
	{
		return PI * radius * radius;
	}

	bool Circle::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return ((position - GetCentre()).Size2() < GetRadius2());
	}

	void Circle::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Circle& circle)
	{
		j["type"] = "circle";
		j["centre"] = circle.GetCentre();
		j["radius"] = circle.GetRadius();
	}
}