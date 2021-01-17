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
		: x(static_cast<int>(v.x)), y(static_cast<int>(v.y)), z(static_cast<int>(v.z))
	{

	}

	Vec3i::Vec3i(int s)
		: x(s), y(s), z(s)
	{
	}

	Vec3i Vec3i::GeneratePoisson(double mean)
	{
		return
		{
			Random::GeneratePoisson(mean),
			Random::GeneratePoisson(mean),
			Random::GeneratePoisson(mean)
		};
	}

	Vec3i Vec3i::GenerateIntUniform(int lower_bound, int upper_bound)
	{
		return
		{
			Random::GenerateIntUniform(lower_bound, upper_bound),
			Random::GenerateIntUniform(lower_bound, upper_bound),
			Random::GenerateIntUniform(lower_bound, upper_bound)
		};
	}

	Vec3i Vec3i::Abs() const
	{
		return { std::abs(x), std::abs(y), std::abs(z) };
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

	int Vec3i::Sum() const
	{
		return x + y + z;
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
		if (!v.x) x = 0;
		if (!v.y) y = 0;
		if (!v.z) z = 0;
	}

	Vec3i Vec3i::operator * (const Vec3b& v) const
	{
		return { x * static_cast<int>(v.x), y * static_cast<int>(v.y), z * static_cast<int>(v.z) };
	}

	Vec3i operator * (const Vec3b& b, const Vec3i& v)
	{
		return { static_cast<int>(b.x) * v.x, static_cast<int>(b.y) * v.y, static_cast<int>(b.z) * v.z };
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

	void Vec3i::Clip(const Vec3i& lower_bound, const Vec3i& upper_bound)
	{
		EqualIf(*this < lower_bound, lower_bound);
		EqualIf(*this > upper_bound, upper_bound);
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