#include "pch.h"
#include "generating_box_2d.h"

namespace accord::shape::generating
{
	Box2D::Box2D(Vec2d origin, Vec2d length)
		: basic::Box2D(origin, length), Surface3DShape()
	{

	}

	Vec2d Box2D::GeneratePointOnSurface() const
	{
		return { Random::GenerateRealUniform(GetOrigin().x, GetEnd().x) ,
			Random::GenerateRealUniform(GetOrigin().y, GetEnd().y)
		};
	}

	void Box2D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box2D>(*this);
	}
}
