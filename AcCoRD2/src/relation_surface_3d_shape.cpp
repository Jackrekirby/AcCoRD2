#pragma once
#include "pch.h"
#include "relation_surface_3d_shape.h"

namespace accord::shape::relation
{
	bool Surface3DShape::IsOverlapping(const Surface3DShape& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Surface3DShape::IsEnveloping(const Surface3DShape& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Surface3DShape::IsEnvelopedBy(const Surface3DShape& other) const
	{
		return other.IsEnveloping(*this);
	}

	void to_json(Json& j, const Surface3DShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}