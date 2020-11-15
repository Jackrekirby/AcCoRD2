#pragma once

namespace accord::math
{
	struct Vec2d;
}

namespace accord::shapes
{
	class Surface3DShape
	{
	public:
		Surface3DShape() = default;

		virtual bool IsWithinOrOnBorder(const math::Vec2d& position) const = 0;
	};
}