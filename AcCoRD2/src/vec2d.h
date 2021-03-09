// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "axis_2d.h"

namespace accord
{

	struct Vec2b;

	template<typename U>
	struct Vec2;

	struct Vec2d
	{
		union
		{
			struct
			{
				double x, y;
			};

			std::enum_array<Axis2D, double, 2> axis;
		};

		Vec2d(double x, double y);

		explicit Vec2d(double s);

		Vec2d() = default;

		static Vec2d PolarToCartesian(double radius, double theta);

		// Generates a vector with a random direction and random magnitude of maximum 1
		static Vec2d GenerateRandomPolar();

		// Generates a vector with a random direction and given magnitude
		static Vec2d GenerateRandomPolar(double radius);

		// calculates the absolute value of each axis
		Vec2d Abs() const;

		// returns the larger of x or y
		double Max() const;

		// returns the larger component in each axis of the two vectors
		static Vec2d Max(const Vec2d& v, const Vec2d& u);

		// returns the smaller of x or y
		double Min() const;

		// returns the smaller component in each axis of the two vectors
		static Vec2d Min(const Vec2d& v, const Vec2d& u);

		// area = x * y
		double Area() const;

		// returns the magnitude of the vector
		double Size() const;

		// returns the square of the magnitude of the vector
		double Size2() const;

		Vec2d Normalise() const;

		static double CrossProduct(const Vec2d& v, const Vec2d& u);

		static double DotProduct(const Vec2d& v, const Vec2d& u);

		// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
		Vec2d Reflect(const Vec2d& unit_normal) const;

		static Vec2d Lerp(const Vec2d& origin, const Vec2d& end, double time);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec2d& v)
		{
			return os << "[" << v.x << ", " << v.y << "]";
		}


		Vec2d operator + (const Vec2d& v) const;

		Vec2d operator + (const double s) const;

		friend Vec2d operator + (const double s, const Vec2d& v);

		void operator += (const Vec2d& v);

		Vec2d operator + () const;


		Vec2d operator - (const Vec2d& v) const;

		Vec2d operator - (const double s) const;

		friend Vec2d operator - (const double s, const Vec2d& v);

		void operator -= (const Vec2d& v);

		Vec2d operator - () const;



		Vec2d operator * (const Vec2d& v) const;

		Vec2d operator * (const double s) const;

		friend Vec2d operator * (const double s, const Vec2d& v);

		void operator *= (const Vec2d& v);


		Vec2d operator * (const Vec2b& v) const;

		friend Vec2d operator * (const Vec2b& b, const Vec2d& v);


		Vec2d operator / (const Vec2d& v) const;

		Vec2d operator / (const double s) const;

		friend Vec2d operator / (const double s, const Vec2d& v);

		void operator /= (const Vec2d& v);



		Vec2b operator < (const Vec2d& v) const;

		Vec2b operator > (const Vec2d& v) const;

		Vec2b operator <= (const Vec2d& v) const;

		Vec2b operator >= (const Vec2d& v) const;

		Vec2b operator == (const Vec2d& v) const;
	};

	void to_json(Json& j, const Vec2d& v);
}