#pragma once
#include "vec3d.h"

namespace accord::shape::basic
{
	class Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		void Move(const Vec3d& origin);

		void Resize(const Vec3d& length);

		const Vec3d& GetOrigin() const;

		const Vec3d& GetEnd() const;

		const Vec3d& GetLength() const;
	private:
		Vec3d origin;
		Vec3d end;
		Vec3d length;
	};

	void to_json(Json& j, const Box3D& box);
}
