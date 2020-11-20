#pragma once
#include "pch.h"
#include "relation_surface_shape.h"

namespace accord::shape::relation
{
	bool SurfaceShape::IsOverlapping(const SurfaceShape& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool SurfaceShape::IsEnveloping(const SurfaceShape& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool SurfaceShape::IsEnvelopedBy(const SurfaceShape& other) const
	{
		return other.IsEnveloping(*this);
	}

	void to_json(Json& j, const SurfaceShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}