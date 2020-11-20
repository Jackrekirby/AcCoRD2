#pragma once

namespace accord
{
	struct Vec2d;
}

namespace accord::shape::collision
{
	class SurfaceShape
	{
	public:
		SurfaceShape() = default;

		virtual bool IsWithinOrOnBorder(const Vec2d& position) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const SurfaceShape& surface_shape);
}