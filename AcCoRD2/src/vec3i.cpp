#include "pch.h"

#include "vec3i.h"
#include "vec3b.h"
#include "vec3d.h"

namespace accord
{
	Vec3i::Vec3i(int x, int y, int z)
		: x(x), y(y), z(z)
	{

	}

	Vec3i::Vec3i(const Vec3d& v)
		: x(v.x), y(v.y), z(v.z)
	{

	}

	Vec3i Vec3i::GeneratePoisson(double mean)
	{
		return
		{
			GeneratePoisson(mean),
			GeneratePoisson(mean),
			GeneratePoisson(mean)
		};
	}

	Vec3i Vec3i::GenerateIntUniform(int lower_bound, int upper_bound)
	{
		return
		{
			GenerateIntUniform(lower_bound, upper_bound),
			GenerateIntUniform(lower_bound, upper_bound),
			GenerateIntUniform(lower_bound, upper_bound)
		};
	}

	// returns the larger of x, y or z
	int Vec3i::Max() const
	{
		return ((x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z));
	}

	// returns the larger component in each axis of the two vectors
	Vec3i Vec3i::Max(const Vec3i& v, const Vec3i& u)
	{
		return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y, (v.z > u.z) ? v.z : u.z };
	}

	// returns the smaller of x, y or z
	int Vec3i::Min() const
	{
		return ((x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z));
	}

	// returns the smaller component in each axis of the two vectors
	Vec3i Vec3i::Min(const Vec3i& v, const Vec3i& u)
	{
		return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y,  (v.z < u.z) ? v.z : u.z };
	}

	// volume = x * y * z
	int Vec3i::Volume() const
	{
		return x * y * z;
	}
	


	Vec3i Vec3i::operator + (const Vec3i& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	Vec3i Vec3i::operator + (const int s) const
	{
		return { x + s, y + s, z + s };
	}

	Vec3i operator + (const int s, const Vec3i& v)
	{
		return { s + v.x, s + v.y, s + v.z };
	}

	void Vec3i::operator += (const Vec3i& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vec3i Vec3i::operator + () const
	{
		return { x, y, z };
	}



	Vec3i Vec3i::operator - (const Vec3i& v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	Vec3i Vec3i::operator - (const int s) const
	{
		return { x - s, y - s, z - s };
	}

	Vec3i operator - (const int s, const Vec3i& v)
	{
		return { s - v.x, s - v.y, s - v.z };
	}

	void Vec3i::operator -= (const Vec3i& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vec3i Vec3i::operator - () const
	{
		return { -x, -y, -z };
	}



	Vec3i Vec3i::operator * (const Vec3i& v) const
	{
		return { x * v.x, y * v.y, z * v.z };
	}

	Vec3i Vec3i::operator * (const int s) const
	{
		return { x * s, y * s, z * s };
	}

	Vec3i operator * (const int s, const Vec3i& v)
	{
		return { s * v.x, s * v.y, s * v.z };
	}

	void Vec3i::operator *= (const Vec3i& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	void Vec3i::operator *= (const Vec3b& v)
	{
		if (v.x) x = 0;
		if (v.y) y = 0;
		if (v.z) z = 0;
	}

	// change to if statement like *=
	Vec3i Vec3i::operator * (const Vec3b& v) const
	{
		return { x * static_cast<double>(v.x), y * static_cast<double>(v.y), z * static_cast<double>(v.z) };
	}

	Vec3i operator * (const Vec3b& b, const Vec3i& v)
	{
		return { static_cast<double>(b.x) * v.x, static_cast<double>(b.y) * v.y, static_cast<double>(b.z) * v.z };
	}



	Vec3i Vec3i::operator / (const Vec3i& v) const
	{
		return { x / v.x, y / v.y, z / v.z };
	}

	Vec3i Vec3i::operator / (const int s) const
	{
		return { x / s, y / s, z / s };
	}

	Vec3i operator / (const int s, const Vec3i& v)
	{
		return { s / v.x, s / v.y, s / v.z };
	}

	void Vec3i::operator /= (const Vec3i& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
	}

	
	
	
	Vec3i Vec3i::operator % (const Vec3i& v) const
	{
		return { x % v.x, y % v.y, z % v.z };
	}

	Vec3i Vec3i::operator % (const int s) const
	{
		return { x % s, y % s, z % s };
	}

	Vec3i operator % (const int s, const Vec3i& v)
	{
		return { s % v.x, s % v.y, s % v.z };
	}

	void Vec3i::operator %= (const Vec3i& v)
	{
		x %= v.x;
		y %= v.y;
		z %= v.z;
	}
	
	void Vec3i::EqualIf(const Vec3b& b, const Vec3i& v)
	{
		if (b.x) x = v.x;
		if (b.y) y = v.y;
		if (b.z) z = v.z;
	}

	Vec3b Vec3i::operator < (const Vec3i& v) const
	{
		return { x < v.x, y < v.y, z < v.z };
	}

	Vec3b Vec3i::operator > (const Vec3i& v) const
	{
		return { x > v.x, y > v.y, z > v.z };
	}

	Vec3b Vec3i::operator <= (const Vec3i& v) const
	{
		return { x <= v.x, y <= v.y, z <= v.z };
	}

	Vec3b Vec3i::operator >= (const Vec3i& v) const
	{
		return { x >= v.x, y >= v.y, z >= v.z };
	}

	Vec3b Vec3i::operator == (const Vec3i& v) const
	{
		return { x == v.x, y == v.y, z == v.z };
	}

	void to_json(Json& j, const Vec3i& v)
	{
		j = { v.x, v.y, v.z };
	}
}