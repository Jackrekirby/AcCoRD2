#pragma once
#include "pch.h"
#include "axis_3d.h"

namespace accord
{
	struct Vec3b;
	struct Vec3d;

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

			std::enum_array<Axis3D, int, 3> axis;
		};

		Vec3i(int x, int y, int z);

		Vec3i() = default;

		Vec3i(const Vec3d& v);

		static Vec3i FromScalar(int s);

		static Vec3i GeneratePoisson(double mean);

		static Vec3i GenerateIntUniform(int lower_bound, int upper_bound);



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

		void operator *= (const Vec3b& v);

		Vec3i operator * (const Vec3b& v) const;

		friend Vec3i operator * (const Vec3b& b, const Vec3i& v);



		Vec3i operator / (const Vec3i& v) const;

		Vec3i operator / (const int s) const;

		friend Vec3i operator / (const int s, const Vec3i& v);

		void operator /= (const Vec3i& v);
		
		void EqualIf(const Vec3b& b, const Vec3i& v);
		
		void Wrap(const Vec3i& lower_bound, const Vec3i& upper_bound);

		
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