// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3b.h"

namespace accord
{
	// currently unused / untested
	// create a vector with 3 dimensions of any type
	// prefer use of a specific type vector (e.g. vec3d)
	template <typename T>
	struct Vec3
	{
		union
		{
			// acces vector by x, y and z dimensions or via array
			struct
			{
				T x, y, z;
			};

			// must access array by enum. see enum_array
			std::enum_array<Axis3D, T, 3> axis;
		};

		Vec3(T x, T y, T z)
			: x(x), y(y), z(z)
		{

		}

		// apply same value across all dimensions
		explicit Vec3(T s)
			: x(s), y(s), z(s)
		{

		}

		Vec3() = default;

		template<typename U>
		Vec3(Vec3<U> v)
		{
			x = static_cast<T>(v.x);
			y = static_cast<T>(v.y);
			y = static_cast<T>(v.z);
		}

		Vec3 operator + (const Vec3& v) const
		{
			return { x + v.x, y + v.y, z + v.z };
		}

		Vec3 operator + (const T s) const
		{
			return { x + s, y + s, z + s };
		}

		friend Vec3 operator + (const T s, const Vec3& v)
		{
			return { s + v.x, s + v.y, s + v.z };
		}

		void operator += (const Vec3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}


		Vec3 operator - (const Vec3& v) const
		{
			return { x - v.x, y - v.y, z - v.z };
		}

		Vec3 operator - (const T s) const
		{
			return { x - s, y - s, z - s };
		}

		friend Vec3 operator - (const T s, const Vec3& v)
		{
			return { s - v.x, s - v.y, s - v.z };
		}

		void operator -= (const Vec3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}


		Vec3 operator * (const Vec3& v) const
		{
			return { x * v.x, y * v.y, z * v.z };
		}

		Vec3 operator * (const T s) const
		{
			return { x * s, y * s, z * s };
		}

		friend Vec3 operator * (const T s, const Vec3& v)
		{
			return { s * v.x, s * v.y, s * v.z };
		}

		void operator *= (const Vec3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}


		Vec3 operator / (const Vec3& v) const
		{
			return { x / v.x, y / v.y, z / v.z };
		}

		Vec3 operator / (const T s) const
		{
			return { x / s, y / s, z / s };
		}

		friend Vec3 operator / (const T s, const Vec3& v)
		{
			return { s / v.x, s / v.y, s / v.z };
		}

		void operator /= (const Vec3& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
		}



		Vec3b operator < (const Vec3& v) const
		{
			return { x < v.x, y < v.y, z < v.z };
		}

		Vec3b operator > (const Vec3& v) const
		{
			return { x > v.x, y > v.y, z > v.z };
		}

		Vec3b operator <= (const Vec3& v) const
		{
			return { x <= v.x, y <= v.y, z <= v.z };
		}

		Vec3b operator >= (const Vec3& v) const
		{
			return { x >= v.x, y >= v.y, z >= v.z };
		}

		Vec3b operator == (const Vec3& v) const
		{
			return { x == v.x, y == v.y, z == v.z };
		}

		Vec3b operator != (const Vec3& v) const
		{
			return { x != v.x, y != v.y, z != v.z };
		}


		// returns the larger of x, y or z
		T Max() const
		{
			return ((x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z));
		}

		// returns the larger component in each axis of the two vectors
		static Vec3 Max(const Vec3& v, const Vec3& u)
		{
			return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y, (v.z > u.z) ? v.z : u.z };
		}

		// returns the smaller of x, y or z
		T Min() const
		{
			return ((x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z));
		}

		// returns the smaller component in each axis of the two vectors
		static Vec3 Min(const Vec3& v, const Vec3& u)
		{
			return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y,  (v.z < u.z) ? v.z : u.z };
		}

		// volume = x * y * z
		T Volume() const
		{
			return x * y * z;
		}

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3& v)
		{
			return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		}
	};

	template<typename T>
	void to_json(Json& j, const Vec3<T>& v)
	{
		j = { v.x, v.y, v.z };
	}

	template<typename T>
	void from_json(const Json& j, Vec3<T>& v) {
		j.at(0).get_to(v.x);
		j.at(1).get_to(v.y);
		j.at(2).get_to(v.z);
	}
}
