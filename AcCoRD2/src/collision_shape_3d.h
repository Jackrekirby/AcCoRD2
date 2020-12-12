#pragma once
#include "pch.h"
#include "collision_3d.h"

namespace accord
{
	struct Vec3d;
	enum class Axis3D;
}

namespace accord::shape::collision
{
	class Shape3D
	{
	public:
		Shape3D() = default;

		virtual std::optional<Collision3D> CalculateExternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<Collision3D> CalculateInternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const = 0;
	
		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape3D& shape);
}