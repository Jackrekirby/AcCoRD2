#pragma once
#include "vec3d.h"
#include "vec2d.h"
#include "axis_3d.h"
#include "basic_shape_3d.h"
#include "basic_box.h"

namespace accord::shape::basic
{
	class Cylinder : public Shape3D
	{
	public:
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		Box GenerateBoundingBox() const;

		void Move(Vec3d base_centre);

		void SetRadius(double radius);

		void SetLength(double length);

		const Vec3d& GetBaseCentre() const;

		double GetRadius() const;

		double GetRadius2() const;

		double GetLength() const;

		double GetBase() const;

		double GetTop() const;

		Axis3D GetAxis() const;

		Vec2d GetCircleCentre() const;

		double CalculateVolume() const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		bool IsWithinBorder(const Vec3d& position) const;

		// only checks faces (base and top) as curved surfaces cannot be checked accurately
		bool IsOnFace(const Vec3d& position) const;

		void ToJson(Json& j) const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Cylinder& cylinder)
		{
			return os << fmt::format("base centre = {}, radius = {}, length = {}, axis = {}",
				cylinder.GetBaseCentre(), cylinder.GetRadius(), cylinder.GetLength(),
				cylinder.GetAxis());
		}

	private:
		Vec3d base_centre; // centre of the base (face with smaller position value)
		Vec2d circle_centre; // circle_centre = base_centre.GetPlane(axis)
		double base; // base = base_centre.GetAxis(axis)
		double length;
		double top; // top = base + length
		double radius;
		double radius2; // radius * radius
		Axis3D axis;
	};

	void to_json(Json& j, const Cylinder& cylinder);
}