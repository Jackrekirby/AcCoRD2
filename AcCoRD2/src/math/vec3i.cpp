#include "vec3i.h"
#include "vec3b.h"

namespace accord::math
{
	Vec3i::Vec3i(int x, int y, int z)
		: x(x), y(y), z(z)
	{

	}

	Vec3i::Vec3i(int a)
		: x(a), y(a), z(a)
	{

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