#pragma once

namespace accord
{
	struct Vec2d;
}

// At the moment not all 2d collision shapes don't need te be able to calculate collision time, 
// intersection and reflection with molecules. 
// They will need to in future when surface diffusion is allowed.
namespace accord::shape::collision
{
	class Shape2D
	{
	public:
		Shape2D() = default;

		virtual bool IsWithinOrOnBorder(const Vec2d& position) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape2D& shape);
}