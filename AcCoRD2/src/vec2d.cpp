#include "pch.h"

#include "vec2d.h"
#include "vec2b.h"

namespace accord
{
	Vec2d::Vec2d(double x, double y)
		: x(x), y(y)
	{

	}

	Vec2d::Vec2d(double s)
		: x(s), y(s)
	{

	}

	Vec2d Vec2d::PolarToCartesian(double radius, double theta)
	{
		return { radius * std::cos(theta), radius * std::sin(theta) };
	}

	// calculates the absolute value of each axis
	Vec2d Vec2d::Abs() const
	{
		return { std::abs(x), std::abs(y) };
	}

	// returns the larger of x or y
	double Vec2d::Max() const
	{
		return ((x > y) ? x : y);
	}

	// returns the larger component in each axis of the two vectors
	Vec2d Vec2d::Max(const Vec2d& v, const Vec2d& u)
	{
		return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y };
	}

	// returns the smaller of x or y
	double Vec2d::Min() const
	{
		return ((x < y) ? x : y);
	}

	// returns the smaller component in each axis of the two vectors
	Vec2d Vec2d::Min(const Vec2d& v, const Vec2d& u)
	{
		return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y };
	}

	// area = x * y
	double Vec2d::Area() const
	{
		return x * y;
	}

	double Vec2d::Size() const
	{
		return sqrt((x * x) + (y * y));
	}

	double Vec2d::Size2() const
	{
		return ((x * x) + (y * y));
	}

	Vec2d Vec2d::Normalise() const
	{
		double m = Size();
		return { x / m, y / m};
	}

	double Vec2d::CrossProduct(const Vec2d& v, const Vec2d& u)
	{
		return ((v.x * u.y) - (v.y * u.x));
	}

	double Vec2d::DotProduct(const Vec2d& v, const Vec2d& u)
	{
		return ((v.x * u.x) + (v.y * u.y));
	}

	// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
	Vec2d Vec2d::Reflect(const Vec2d& unit_normal) const
	{
		return (*this - 2 * DotProduct(*this, unit_normal) * unit_normal);
	}

	Vec2d Vec2d::Lerp(const Vec2d& origin, const Vec2d& end, double time)
	{
		return origin + time * (end - origin);
	}

	Vec2d Vec2d::operator + (const Vec2d& v) const
	{
		return { x + v.x, y + v.y };
	}

	Vec2d Vec2d::operator + (const double s) const
	{
		return { x + s, y + s };
	}

	Vec2d operator + (const double s, const Vec2d& v)
	{
		return { s + v.x, s + v.y };
	}

	void Vec2d::operator += (const Vec2d& v)
	{
		x += v.x;
		y += v.y;
	}

	Vec2d Vec2d::operator + () const
	{
		return { x, y };
	}


	Vec2d Vec2d::operator - (const Vec2d& v) const
	{
		return { x - v.x, y - v.y };
	}

	Vec2d Vec2d::operator - (const double s) const
	{
		return { x - s, y - s };
	}

	Vec2d operator - (const double s, const Vec2d& v)
	{
		return { s - v.x, s - v.y };
	}

	void Vec2d::operator -= (const Vec2d& v)
	{
		x -= v.x;
		y -= v.y;
	}

	Vec2d Vec2d::operator - () const
	{
		return { -x, -y };
	}



	Vec2d Vec2d::operator * (const Vec2d& v) const
	{
		return { x * v.x, y * v.y };
	}

	Vec2d Vec2d::operator * (const double s) const
	{
		return { x * s, y * s };
	}

	Vec2d operator * (const double s, const Vec2d& v)
	{
		return { s * v.x, s * v.y };
	}

	void Vec2d::operator *= (const Vec2d& v)
	{
		x *= v.x;
		y *= v.y;
	}


	Vec2d Vec2d::operator * (const Vec2b& v) const
	{
		return { x * static_cast<double>(v.x), y * static_cast<double>(v.y) };
	}

	Vec2d operator * (const Vec2b& b, const Vec2d& v)
	{
		return { static_cast<double>(b.x) * v.x, static_cast<double>(b.y) * v.y };
	}



	Vec2d Vec2d::operator / (const Vec2d& v) const
	{
		return { x / v.x, y / v.y };
	}

	Vec2d Vec2d::operator / (const double s) const
	{
		return { x / s, y / s };
	}

	Vec2d operator / (const double s, const Vec2d& v)
	{
		return { s / v.x, s / v.y };
	}

	void Vec2d::operator /= (const Vec2d& v)
	{
		x /= v.x;
		y /= v.y;
	}



	Vec2b Vec2d::operator < (const Vec2d& v) const
	{
		return { x < v.x, y < v.y };
	}

	Vec2b Vec2d::operator > (const Vec2d& v) const
	{
		return { x > v.x, y > v.y };
	}

	Vec2b Vec2d::operator <= (const Vec2d& v) const
	{
		return { x <= v.x, y <= v.y };
	}

	Vec2b Vec2d::operator >= (const Vec2d& v) const
	{
		return { x >= v.x, y >= v.y };
	}

	Vec2b Vec2d::operator == (const Vec2d& v) const
	{
		return { x == v.x, y == v.y };
	}

	void to_json(Json& j, const Vec2d& v)
	{
		j = { v.x, v.y };
	}
}