#pragma once
#include "json.h"

#include <array>

namespace AcCoRD::math
{
	struct Vec3b;

	template<typename U>
	struct Vec3;

	struct Vec3d
	{
		union
		{
			struct
			{
				double x, y, z;
			};

			std::array<double, 3> axis;
		};

		Vec3d(double x, double y, double z);

		Vec3d(double a);

		Vec3d() = default;

		template<typename T>
		Vec3d(T v)
		{
			x = static_cast<double>(v.x);
			y = static_cast<double>(v.y);
			z = static_cast<double>(v.z);
		}

		// returns the larger of x, y or z
		double Max() const;

		// returns the larger component in each axis of the two vectors
		static Vec3d Max(const Vec3d& v, const Vec3d& u);

		// returns the smaller of x, y or z
		double Min() const;

		// returns the smaller component in each axis of the two vectors
		static Vec3d Min(const Vec3d& v, const Vec3d& u);

		// volume = x * y * z
		double Volume() const;

		// returns the magnitude of the vector
		double Size() const;

		// returns the square of the magnitude of the vector
		double Size2() const;

		Vec3d Normalise() const;

		static Vec3d CrossProduct(const Vec3d & v, const Vec3d & u);

		static double DotProduct(const Vec3d & v, const Vec3d & u);

		// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
		Vec3d Reflect(const Vec3d & unit_normal) const;

		static Vec3d Lerp(const Vec3d & origin, const Vec3d & end, double time);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3d& v)
		{
			return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		}

		Vec3d operator + (const Vec3d& v) const;

		Vec3d operator + (const double s) const;

		friend Vec3d operator + (const double s, const Vec3d& v);

		void operator += (const Vec3d& v);

		Vec3d operator + () const;


		Vec3d operator - (const Vec3d& v) const;

		Vec3d operator - (const double s) const;

		friend Vec3d operator - (const double s, const Vec3d& v);

		void operator -= (const Vec3d& v);

		Vec3d operator - () const;



		Vec3d operator * (const Vec3d& v) const;

		Vec3d operator * (const double s) const;

		friend Vec3d operator * (const double s, const Vec3d& v);

		void operator *= (const Vec3d& v);



		Vec3d operator / (const Vec3d& v) const;

		Vec3d operator / (const double s) const;

		friend Vec3d operator / (const double s, const Vec3d& v);

		void operator /= (const Vec3d& v);



		Vec3b operator < (const Vec3d& v) const;

		Vec3b operator > (const Vec3d& v) const;

		Vec3b operator <= (const Vec3d& v) const;

		Vec3b operator >= (const Vec3d& v) const;

		Vec3b operator == (const Vec3d& v) const;

	};

	void to_json(Json& j, const Vec3d& v);

}