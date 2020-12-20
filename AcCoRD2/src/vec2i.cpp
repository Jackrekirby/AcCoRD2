#include "pch.h"

#include "vec2i.h"
#include "vec2b.h"

namespace accord
{
	Vec2i::Vec2i(int x, int y)
		: x(x), y(y)
	{

	}

	Vec2i::Vec2i(int s)
		: x(s), y(s)
	{

	}

	// returns the larger of x or y
	int Vec2i::Max() const
	{
		return ((x > y) ? x : y);
	}

	// returns the larger component in each axis of the two vectors
	Vec2i Vec2i::Max(const Vec2i& v, const Vec2i& u)
	{
		return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y };
	}

	// returns the smaller of x or y
	int Vec2i::Min() const
	{
		return ((x < y) ? x : y);
	}

	// returns the smaller component in each axis of the two vectors
	Vec2i Vec2i::Min(const Vec2i& v, const Vec2i& u)
	{
		return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y };
	}

	// area = x * y
	int Vec2i::Area() const
	{
		return x * y;
	}

	Vec2i Vec2i::operator + (const Vec2i& v) const
	{
		return { x + v.x, y + v.y };
	}

	Vec2i Vec2i::operator + (const int s) const
	{
		return { x + s, y + s };
	}

	Vec2i operator + (const int s, const Vec2i& v)
	{
		return { s + v.x, s + v.y };
	}

	void Vec2i::operator += (const Vec2i& v)
	{
		x += v.x;
		y += v.y;
	}

	Vec2i Vec2i::operator + () const
	{
		return { x, y };
	}


	Vec2i Vec2i::operator - (const Vec2i& v) const
	{
		return { x - v.x, y - v.y };
	}

	Vec2i Vec2i::operator - (const int s) const
	{
		return { x - s, y - s };
	}

	Vec2i operator - (const int s, const Vec2i& v)
	{
		return { s - v.x, s - v.y };
	}

	void Vec2i::operator -= (const Vec2i& v)
	{
		x -= v.x;
		y -= v.y;
	}

	Vec2i Vec2i::operator - () const
	{
		return { -x, -y };
	}



	Vec2i Vec2i::operator * (const Vec2i& v) const
	{
		return { x * v.x, y * v.y };
	}

	Vec2i Vec2i::operator * (const int s) const
	{
		return { x * s, y * s };
	}

	Vec2i operator * (const int s, const Vec2i& v)
	{
		return { s * v.x, s * v.y };
	}

	void Vec2i::operator *= (const Vec2i& v)
	{
		x *= v.x;
		y *= v.y;
	}



	Vec2i Vec2i::operator / (const Vec2i& v) const
	{
		return { x / v.x, y / v.y };
	}

	Vec2i Vec2i::operator / (const int s) const
	{
		return { x / s, y / s };
	}

	Vec2i operator / (const int s, const Vec2i& v)
	{
		return { s / v.x, s / v.y };
	}

	void Vec2i::operator /= (const Vec2i& v)
	{
		x /= v.x;
		y /= v.y;
	}
	
	
	
	Vec2i Vec2i::operator % (const Vec2i& v) const
	{
		return { x % v.x, y % v.y };
	}

	Vec2i Vec2i::operator % (const int s) const
	{
		return { x % s, y % s };
	}

	Vec2i operator % (const int s, const Vec2i& v)
	{
		return { s % v.x, s % v.y };
	}

	void Vec2i::operator %= (const Vec2i& v)
	{
		x %= v.x;
		y %= v.y;
	}



	Vec2b Vec2i::operator < (const Vec2i& v) const
	{
		return { x < v.x, y < v.y };
	}

	Vec2b Vec2i::operator > (const Vec2i& v) const
	{
		return { x > v.x, y > v.y };
	}

	Vec2b Vec2i::operator <= (const Vec2i& v) const
	{
		return { x <= v.x, y <= v.y };
	}

	Vec2b Vec2i::operator >= (const Vec2i& v) const
	{
		return { x >= v.x, y >= v.y };
	}

	Vec2b Vec2i::operator == (const Vec2i& v) const
	{
		return { x == v.x, y == v.y };
	}

	void to_json(Json& j, const Vec2i& v)
	{
		j = { v.x, v.y };
	}

}