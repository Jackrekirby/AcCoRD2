// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "axis_2d.h"

namespace accord
{
	struct Vec2b;

	template <typename T>
	struct Vec2
	{
		union
		{
			struct
			{
				T x, y;
			};

			std::enum_array<Axis2D, T, 2> axis;
		};

		Vec2(T x, T y)
			: x(x), y(y)
		{

		}

		explicit Vec2(T s)
			: x(s), y(s)
		{

		}

		Vec2() = default;

		template<typename U>
		Vec2(Vec2<U> v)
		{
			x = static_cast<T>(v.x);
			y = static_cast<T>(v.y);
		}

		Vec2 operator + (const Vec2& v) const
		{
			return { x + v.x, y + v.y };
		}

		Vec2 operator + (const T s) const
		{
			return { x + s, y + s };
		}

		friend Vec2 operator + (const T s, const Vec2& v)
		{
			return { s + v.x, s + v.y };
		}

		void operator += (const Vec2& v)
		{
			x += v.x;
			y += v.y;
		}

		Vec2 operator + () const
		{
			return { x, y };
		}


		Vec2 operator - (const Vec2& v) const
		{
			return { x - v.x, y - v.y };
		}

		Vec2 operator - (const T s) const
		{
			return { x - s, y - s };
		}

		friend Vec2 operator - (const T s, const Vec2& v)
		{
			return { s - v.x, s - v.y };
		}

		void operator -= (const Vec2& v)
		{
			x -= v.x;
			y -= v.y;
		}

		Vec2 operator - () const
		{
			return { -x, -y };
		}


		Vec2 operator * (const Vec2& v) const
		{
			return { x * v.x, y * v.y };
		}

		Vec2 operator * (const T s) const
		{
			return { x * s, y * s };
		}

		friend Vec2 operator * (const T s, const Vec2& v)
		{
			return { s * v.x, s * v.y };
		}

		void operator *= (const Vec2& v)
		{
			x *= v.x;
			y *= v.y;
		}


		Vec2 operator / (const Vec2& v) const
		{
			return { x / v.x, y / v.y };
		}

		Vec2 operator / (const T s) const
		{
			return { x / s, y / s };
		}

		friend Vec2 operator / (const T s, const Vec2& v)
		{
			return { s / v.x, s / v.y };
		}

		void operator /= (const Vec2& v)
		{
			x /= v.x;
			y /= v.y;
		}


		Vec2b operator < (const Vec2& v) const
		{
			return { x < v.x, y < v.y };
		}

		Vec2b operator > (const Vec2& v) const
		{
			return { x > v.x, y > v.y };
		}

		Vec2b operator <= (const Vec2& v) const
		{
			return { x <= v.x, y <= v.y };
		}

		Vec2b operator >= (const Vec2& v) const
		{
			return { x >= v.x, y >= v.y };
		}

		Vec2b operator == (const Vec2& v) const
		{
			return { x == v.x, y == v.y };
		}

		Vec2b operator != (const Vec2& v) const
		{
			return { x != v.x, y != v.y };
		}


		// returns the larger of x or y
		T Max() const
		{
			return ((x > y) ? x : y);
		}

		// returns the larger component in each axis of the two vectors
		static Vec2 Max(const Vec2& v, const Vec2& u)
		{
			return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y };
		}

		// returns the smaller of x or y
		T Min() const
		{
			return ((x < y) ? x : y);
		}

		// returns the smaller component in each axis of the two vectors
		static Vec2 Min(const Vec2& v, const Vec2& u)
		{
			return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y };
		}

		// area = x * y
		T Area() const
		{
			return x * y;
		}

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec2& v)
		{
			return os << "[ " << v.x << ", " << v.y << " ]";
		}
	};

	template<typename T>
	void to_json(Json& j, const Vec2<T>& v)
	{
		j = { v.x, v.y };
	}
}
