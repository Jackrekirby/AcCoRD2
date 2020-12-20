#pragma once
#include "pch.h"
#include "vec2d.h"
#include "axis_3d.h"

namespace accord
{
	struct Vec3b;
	struct Vec3i;
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

			std::enum_array<Axis3D, double, 3> axis;
		};

		Vec3d(double x, double y, double z);

		Vec3d() = default;

		Vec3d(const Vec3i& v);

		explicit Vec3d(double s);

		Vec3d(double longitudinal, const Vec2d& transverse, Axis3D axis);

		// consider renaming to RandomExponential()
		static Vec3d GenerateExponential(double mean);

		static Vec3d GenerateNormal(double mean = 0.0, double std = 1.0);

		static Vec3d GenerateTriangular();

		static Vec3d GenerateUniform(double lower_bound = 0.0, double upper_bound = 1.0);

		static Vec3d PolarToCartesian(double radius, double theta, double phi);

		double GetAxis(Axis3D axis) const;

		Vec2d GetPlane(Axis3D axis) const;

		// calculates the absolute value of each axis
		Vec3d Abs() const;

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


		Vec3d operator * (const Vec3b& v) const;

		friend Vec3d operator * (const Vec3b& b, const Vec3d& v);



		Vec3d operator / (const Vec3d& v) const;

		Vec3d operator / (const double s) const;

		friend Vec3d operator / (const double s, const Vec3d& v);

		void operator /= (const Vec3d& v);


		void EqualIf(const Vec3b& b, const Vec3d& v);

		void Clip(const Vec3d& lower_bound, const Vec3d& upper_bound);

		Vec3b operator < (const Vec3d& v) const;

		Vec3b operator > (const Vec3d& v) const;

		Vec3b operator <= (const Vec3d& v) const;

		Vec3b operator >= (const Vec3d& v) const;

		Vec3b operator == (const Vec3d& v) const;

	};

	void to_json(Json& j, const Vec3d& v);

}