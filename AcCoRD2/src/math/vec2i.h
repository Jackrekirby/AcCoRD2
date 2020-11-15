#pragma once

#include <array>
#include "json.h"

namespace accord::math
{

	struct Vec2b;

	template<typename U>
	struct Vec2;

	struct Vec2i
	{
		union
		{
			struct
			{
				int x, y;
			};

			std::array<int, 2> axis;
		};

		Vec2i(int x, int y);

		Vec2i() = default;

		// returns the larger of x or y
		int Max() const;

		// returns the larger component in each axis of the two vectors
		static Vec2i Max(const Vec2i& v, const Vec2i& u);

		// returns the smaller of x or y
		int Min() const;

		// returns the smaller component in each axis of the two vectors
		static Vec2i Min(const Vec2i& v, const Vec2i& u);

		// area = x * y
		int Area() const;

		// returns the magnitude of the vector
		int Size() const;

		// returns the square of the magnitude of the vector
		int Size2() const;

		Vec2i Normalise() const;

		static Vec2i CrossProduct(const Vec2i& v, const Vec2i& u);

		static int DotProduct(const Vec2i& v, const Vec2i& u);

		// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
		Vec2i Reflect(const Vec2i& unit_normal) const;

		static Vec2i Lerp(const Vec2i& origin, const Vec2i& end, int time);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec2i& v)
		{
			return os << "[" << v.x << ", " << v.y << "]";
		}

		Vec2i operator + (const Vec2i& v) const;

		Vec2i operator + (const int s) const;

		friend Vec2i operator + (const int s, const Vec2i& v);

		void operator += (const Vec2i& v);

		Vec2i operator + () const;


		Vec2i operator - (const Vec2i& v) const;

		Vec2i operator - (const int s) const;

		friend Vec2i operator - (const int s, const Vec2i& v);

		void operator -= (const Vec2i& v);

		Vec2i operator - () const;



		Vec2i operator * (const Vec2i& v) const;

		Vec2i operator * (const int s) const;

		friend Vec2i operator * (const int s, const Vec2i& v);

		void operator *= (const Vec2i& v);



		Vec2i operator / (const Vec2i& v) const;

		Vec2i operator / (const int s) const;

		friend Vec2i operator / (const int s, const Vec2i& v);

		void operator /= (const Vec2i& v);


		
		Vec2i operator % (const Vec2i& v) const;

		Vec2i operator % (const int s) const;

		friend Vec2i operator % (const int s, const Vec2i& v);

		void operator %= (const Vec2i& v);
		
		

		Vec2b operator < (const Vec2i& v) const;

		Vec2b operator > (const Vec2i& v) const;

		Vec2b operator <= (const Vec2i& v) const;

		Vec2b operator >= (const Vec2i& v) const;

		Vec2b operator == (const Vec2i& v) const;
	};

	void to_json(Json& j, const Vec2i& v);
}