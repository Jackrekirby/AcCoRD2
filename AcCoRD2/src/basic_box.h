#pragma once
#include "vec3d.h"
#include "box_faces.h"

namespace accord::shape::basic
{
	class Box
	{
	public:
		Box(Vec3d origin, Vec3d length);

		void Move(const Vec3d& origin);

		void Resize(const Vec3d& length);

		const Vec3d& GetOrigin() const;

		const Vec3d& GetEnd() const;

		const Vec3d& GetLength() const;

		double CalculateVolume() const;
	private:
		Vec3d origin;
		Vec3d end;
		Vec3d length;
	};

	void to_json(Json& j, const Box& box);
}
