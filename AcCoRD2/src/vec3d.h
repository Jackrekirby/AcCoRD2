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
			// access vector via x, y and z dimensions or as an array
			struct
			{
				double x, y, z;
			};

			// must access array by enum. see enum_array
			std::enum_array<Axis3D, double, 3> axis;
		};

		Vec3d(double x, double y, double z);

		// construct a vector with zero dimensions
		Vec3d() = default;

		// convert an integer vector to a double vector
		Vec3d(const Vec3i& v);

		// construct a vector with the same value along each dimension
		explicit Vec3d(double s);

		// construct a 3D vector which is defined by is longitidinal position along a specified axis
		// and its position perpendicular to the axis.
		// The tranverse dimensions are ordered y,z x,z or x,y dependening on the specified axis
		Vec3d(double longitudinal, const Vec2d& transverse, Axis3D axis);

		
		// Generate random numbers along each axis. see random.h for the types of random numbers
		static Vec3d GenerateExponential(double mean);

		static Vec3d GenerateNormal(double mean = 0.0, double std = 1.0);

		static Vec3d GenerateTriangular();

		static Vec3d GenerateUniform(double lower_bound = 0.0, double upper_bound = 1.0);

		// construct a vector using a radius, and angle theta in the x-y plane and angle phi in the z plane
		static Vec3d PolarToCartesian(double radius, double theta, double phi);

		// generate a equally distributed random number which has a radius between 0 and 1,
		// and random angle theta and phi. see PolarToCartesian.
		static Vec3d GenerateRandomPolar();

		// generate a equally distributed random number which has set radius
		// but a random angle theta and phi. see PolarToCartesian.
		static Vec3d GenerateRandomPolar(double radius);

		// returns the value of the vector in specified axis
		double GetAxis(Axis3D axis) const;

		// returns the value in the vector in the dimensions perpendicular to the specified axis
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

		// returns the smallest Axis
		Axis3D MinAxis() const;

		// volume = x * y * z
		double Volume() const;

		// returns the magnitude of the vector
		double Size() const;

		// returns the square of the magnitude of the vector
		double Size2() const;

		// returns a vector of equal direction and magnitude 1
		Vec3d Normalise() const;

		// calculate cross product between vectors v and u
		static Vec3d CrossProduct(const Vec3d & v, const Vec3d & u);

		// calculate dot product between vectors v and u
		static double DotProduct(const Vec3d & v, const Vec3d & u);

		// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
		Vec3d Reflect(const Vec3d & unit_normal) const;

		// linearly interpolate between the two points, 'origin' and 'end' where origin is at time = 0, and end is at time = 1.
		static Vec3d Lerp(const Vec3d & origin, const Vec3d & end, double time);

		// log vector to output stream
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

		// sets each dimension to that specified by vector v if b is true in that dimension
		void EqualIf(const Vec3b& b, const Vec3d& v);

		// clip the vector to between a lower and upper bound, inclusive of those bounds
		void Clip(const Vec3d& lower_bound, const Vec3d& upper_bound);

		// conditional operators return true along each dimension if condition satisfied
		Vec3b operator < (const Vec3d& v) const;

		Vec3b operator > (const Vec3d& v) const;

		Vec3b operator <= (const Vec3d& v) const;

		Vec3b operator >= (const Vec3d& v) const;

		Vec3b operator == (const Vec3d& v) const;

	};

	// convert vector data to json
	void to_json(Json& j, const Vec3d& v);

	// create a vector from json data
	void from_json(const Json& j, Vec3d& v);

}