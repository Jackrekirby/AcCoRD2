#include "pch.h"
#include "vec3d.h"
#include "vec3b.h"
#include "vec3.h"
#include "vec3i.h"


namespace accord
{
	Vec3d::Vec3d(double x, double y, double z)
		: x(x), y(y), z(z)
	{

	}

	Vec3d::Vec3d(const Vec3i& v)
		: x(v.x), y(v.y), z(v.z)
	{

	}

	Vec3d Vec3d::GenerateExponential(double mean)
	{
		return {
			Random::GenerateExponential(mean),
			Random::GenerateExponential(mean),
			Random::GenerateExponential(mean)
		};
	}

	Vec3d Vec3d::GenerateNormal(double mean, double std)
	{
		return {
			Random::GenerateNormal(mean, std),
			Random::GenerateNormal(mean, std),
			Random::GenerateNormal(mean, std)
		};
	}

	Vec3d Vec3d::GenerateTriangular()
	{
		return {
			Random::GenerateTriangular(),
			Random::GenerateTriangular(),
			Random::GenerateTriangular()
		};
	}

	Vec3d Vec3d::GenerateUniform(double lower_bound, double upper_bound)
	{
		return {
			Random::GenerateRealUniform(lower_bound, upper_bound),
			Random::GenerateRealUniform(lower_bound, upper_bound),
			Random::GenerateRealUniform(lower_bound, upper_bound)
		};
	}

	Vec3d Vec3d::PolarToCartesian(double radius, double theta, double phi)
	{
		return 
		{ 
			radius * std::cos(theta) * std::sin(phi), 
			radius * std::sin(theta) * std::sin(phi),
			radius * std::cos(phi)
		};
	}

	double Vec3d::GetAxis(Axis3D axis) const
	{
		return this->axis.at(axis);
	}

	Vec2d Vec3d::GetPlane(Axis3D axis) const
	{
		switch (axis)
		{
		case Axis3D::x:
			return { y, z };
		case Axis3D::y:
			return { x, z };
		case Axis3D::z:
			return { x, y };
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}
	// calculates the absolute value of each axis
	Vec3d Vec3d::Abs() const
	{
		return { std::abs(x), std::abs(y), std::abs(z) };
	}

	// returns the larger of x, y or z
	double Vec3d::Max() const
	{
		return ((x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z));
	}

	// returns the larger component in each axis of the two vectors
	Vec3d Vec3d::Max(const Vec3d& v, const Vec3d& u)
	{
		return { (v.x > u.x) ? v.x : u.x, (v.y > u.y) ? v.y : u.y, (v.z > u.z) ? v.z : u.z };
	}

	// returns the smaller of x, y or z
	double Vec3d::Min() const
	{
		return ((x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z));
	}

	// returns the smaller component in each axis of the two vectors
	Vec3d Vec3d::Min(const Vec3d& v, const Vec3d& u)
	{
		return { (v.x < u.x) ? v.x : u.x, (v.y < u.y) ? v.y : u.y,  (v.z < u.z) ? v.z : u.z };
	}

	// volume = x * y * z
	double Vec3d::Volume() const
	{
		return x * y * z;
	}

	double Vec3d::Size() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	double Vec3d::Size2() const
	{
		return ((x * x) + (y * y) + (z * z));
	}

	Vec3d Vec3d::Normalise() const
	{
		double m = Size();
		return { x / m, y / m, z / m };
	}

	Vec3d Vec3d::CrossProduct(const Vec3d& v, const Vec3d& u)
	{
		return { (v.y * u.z) - (v.z * u.y), (v.z * u.x) - (v.x * u.z), (v.x * u.y) - (v.y * u.z) };
	}

	double Vec3d::DotProduct(const Vec3d& v, const Vec3d& u)
	{
		return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
	}

	// Vector is reflected along a mirror plane. The unit_normal vector defines the normal to the mirror plane.
	Vec3d Vec3d::Reflect(const Vec3d& unit_normal) const
	{
		return (*this - 2 * DotProduct(*this, unit_normal) * unit_normal);
	}

	Vec3d Vec3d::Lerp(const Vec3d& origin, const Vec3d& end, double time)
	{
		return origin + time * (end - origin);
	}



	Vec3d Vec3d::operator + (const Vec3d& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	Vec3d Vec3d::operator + (const double s) const
	{
		return { x + s, y + s, z + s };
	}

	Vec3d operator + (const double s, const Vec3d& v)
	{
		return { s + v.x, s + v.y, s + v.z };
	}

	void Vec3d::operator += (const Vec3d& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vec3d Vec3d::operator + () const
	{
		return { x, y, z };
	}



	Vec3d Vec3d::operator - (const Vec3d& v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	Vec3d Vec3d::operator - (const double s) const
	{
		return { x - s, y - s, z - s };
	}

	Vec3d operator - (const double s, const Vec3d& v)
	{
		return { s - v.x, s - v.y, s - v.z };
	}

	void Vec3d::operator -= (const Vec3d& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vec3d Vec3d::operator - () const
	{
		return { -x, -y, -z };
	}



	Vec3d Vec3d::operator * (const Vec3d& v) const
	{
		return { x * v.x, y * v.y, z * v.z };
	}

	Vec3d Vec3d::operator * (const double s) const
	{
		return { x * s, y * s, z * s };
	}

	Vec3d operator * (const double s, const Vec3d& v)
	{
		return { s * v.x, s * v.y, s * v.z };
	}

	void Vec3d::operator *= (const Vec3d& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}


	Vec3d Vec3d::operator * (const Vec3b& v) const
	{
		return { x * static_cast<double>(v.x), y * static_cast<double>(v.y), z * static_cast<double>(v.z) };
	}

	Vec3d operator * (const Vec3b& b, const Vec3d& v)
	{
		return { static_cast<double>(b.x) * v.x, static_cast<double>(b.y) * v.y, static_cast<double>(b.z) * v.z };
	}


	Vec3d Vec3d::operator / (const Vec3d& v) const
	{
		return { x / v.x, y / v.y, z / v.z };
	}

	Vec3d Vec3d::operator / (const double s) const
	{
		return { x / s, y / s, z / s };
	}

	Vec3d operator / (const double s, const Vec3d& v)
	{
		return { s / v.x, s / v.y, s / v.z };
	}

	void Vec3d::operator /= (const Vec3d& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
	}


	void Vec3d::EqualIf(const Vec3b& b, const Vec3d& v)
	{
		if (b.x) x = v.x;
		if (b.y) y = v.y;
		if (b.z) z = v.z;
	}


	Vec3b Vec3d::operator < (const Vec3d& v) const
	{
		return { x < v.x, y < v.y, z < v.z };
	}

	Vec3b Vec3d::operator > (const Vec3d& v) const
	{
		return { x > v.x, y > v.y, z > v.z };
	}

	Vec3b Vec3d::operator <= (const Vec3d& v) const
	{
		return { x <= v.x, y <= v.y, z <= v.z };
	}

	Vec3b Vec3d::operator >= (const Vec3d& v) const
	{
		return { x >= v.x, y >= v.y, z >= v.z };
	}

	Vec3b Vec3d::operator == (const Vec3d& v) const
	{
		return { x == v.x, y == v.y, z == v.z };
	}

	void to_json(Json& j, const Vec3d& v)
	{
		j = { v.x, v.y, v.z };
	}
}