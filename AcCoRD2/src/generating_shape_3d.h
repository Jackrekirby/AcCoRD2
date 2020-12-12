#pragma once
#include "vec3d.h"

namespace accord::shape::generating
{
	class Shape3D
	{
	public:
		Shape3D() = default;

		virtual Vec3d GeneratePointOnSurface() const = 0;

		virtual Vec3d GeneratePointInVolume() const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape3D& shape);
}
