#pragma once
#include "json.h"

#include <array>

namespace AcCoRD::math
{
	struct Vec3b;

	template<typename U>
	struct Vec3;

	struct Vec3i
	{
		union
		{
			struct
			{
				int x, y, z;
			};

			std::array<int, 3> axis;
		};

		Vec3i(int x, int y, int z);

		Vec3i(int a);

		Vec3i() = default;

		template<typename T>
		Vec3i(T v)
		{
			x = static_cast<int>(v.x);
			y = static_cast<int>(v.y);
			z = static_cast<int>(v.z);
		}

		// returns the larger of x, y or z
		int Max() const;

		// returns the larger component in each axis of the two vectors
		static Vec3i Max(const Vec3i& v, const Vec3i& u);

		// returns the smaller of x, y or z
		int Min() const;

		// returns the smaller component in each axis of the two vectors
		static Vec3i Min(const Vec3i& v, const Vec3i& u);

		// volume = x * y * z
		int Volume() const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3i& v)
		{
			return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		}

		Vec3i operator + (const Vec3i& v) const;

		Vec3i operator + (const int s) const;

		friend Vec3i operator + (const int s, const Vec3i& v);

		void operator += (const Vec3i& v);

		Vec3i operator + () const;


		Vec3i operator - (const Vec3i& v) const;

		Vec3i operator - (const int s) const;

		friend Vec3i operator - (const int s, const Vec3i& v);

		void operator -= (const Vec3i& v);

		Vec3i operator - () const;



		Vec3i operator * (const Vec3i& v) const;

		Vec3i operator * (const int s) const;

		friend Vec3i operator * (const int s, const Vec3i& v);

		void operator *= (const Vec3i& v);



		Vec3i operator / (const Vec3i& v) const;

		Vec3i operator / (const int s) const;

		friend Vec3i operator / (const int s, const Vec3i& v);

		void operator /= (const Vec3i& v);
		
		
		
		Vec3i operator % (const Vec3i& v) const;

		Vec3i operator % (const int s) const;

		friend Vec3i operator % (const int s, const Vec3i& v);

		void operator %= (const Vec3i& v);



		Vec3b operator < (const Vec3i& v) const;

		Vec3b operator > (const Vec3i& v) const;

		Vec3b operator <= (const Vec3i& v) const;

		Vec3b operator >= (const Vec3i& v) const;

		Vec3b operator == (const Vec3i& v) const;

	};

	void to_json(Json& j, const Vec3i& v);

}