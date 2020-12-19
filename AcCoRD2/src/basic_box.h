#pragma once
#include "vec3d.h"
#include "box_faces.h"
#include "basic_shape_3d.h"

namespace accord::shape::basic
{
	class Cylinder;
	class Sphere;

	class Box : public Shape3D
	{
	public:
		Box(Vec3d origin, Vec3d length);

		Box(const Cylinder& cylinder);

		Box(const Sphere& sphere);

		Box GenerateBoundingBox() const;

		void Move(const Vec3d& origin);

		void Resize(const Vec3d& length);

		const Vec3d& GetOrigin() const;

		const Vec3d& GetEnd() const;

		const Vec3d& GetLength() const;

		Vec3d CalculateCentre() const;

		double CalculateVolume() const;

		bool IsWithinBorder(const Vec3d& position) const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		bool IsOnBorder(const Vec3d& position) const;

		void ToJson(Json& j) const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Box& box)
		{
			return os << fmt::format("origin = {}, length = {}, end = {}", 
				box.GetOrigin(), box.GetLength(), box.GetEnd());
		}
	private:
		Vec3d origin;
		Vec3d length;
		Vec3d end;
	};

	void to_json(Json& j, const Box& box);
}
