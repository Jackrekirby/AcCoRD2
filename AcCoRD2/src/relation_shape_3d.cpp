#pragma once
#include "pch.h"
#include "relation_shape_3d.h"

namespace accord::shape::relation
{
	bool Shape3D::IsOverlapping(const Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Shape3D::IsEnveloping(const Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Shape3D::IsEnvelopedBy(const Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	void to_json(Json& j, const Shape3D& shape)
	{
		shape.ToJson(j);
	}
}