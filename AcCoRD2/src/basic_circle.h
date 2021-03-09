// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec2d.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	class Circle : public Shape
	{
	public:
		// construct circle from centre point of circle and its radius
		Circle(Vec2d centre, double radius);

		// move the centre position of the circle
		void Move(const Vec2d& centre);

		// chaneg the radius of the circle
		void Resize(double radius);

		// returns the centre of the circle
		const Vec2d& GetCentre() const;

		// returns the radius of the circle
		const double& GetRadius() const;

		// returns the square of the radius of the circle
		const double& GetRadius2() const;

		// returns the area of the circle
		double CalculateArea() const;

		// returns true if the point is inside the radius of the circle, inclusive of surface
		// due to floating point error detecting whether a point lies exactly on the surface is not implemented
		bool IsWithinOrOnBorder(const Vec2d& position) const;
		
		// convert the circle data to json
		void ToJson(Json& j) const;

		// log the circle data to an output stream
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Circle& circle)
		{
			return os << fmt::format("centre = {}, radius = {}",
				circle.GetCentre(), circle.GetRadius());
		}

	private:
		Vec2d centre;
		double radius;
		double radius2; // radius * radius
	};

	// convert circle data to json format
	void to_json(Json& j, const Circle& circle);
}