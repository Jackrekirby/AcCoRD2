#include "pch.h"
#include "generating_box.h"

namespace accord::shape::generating
{
	Rect::Rect(Vec2d origin, Vec2d length)
		: basic::Rect(origin, length), Shape2D()
	{

	}

	Rect::Rect(basic::Rect rect)
		: basic::Rect(rect)
	{
	}

	Vec2d Rect::GeneratePointInArea() const
	{
		return { Random::GenerateRealUniform(GetOrigin().x, GetEnd().x) ,
			Random::GenerateRealUniform(GetOrigin().y, GetEnd().y)
		};
	}

	void Rect::ToJson(Json& j) const
	{
		j = static_cast<basic::Rect>(*this);
	}
}
