// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "relation_shape_2d.h"

namespace accord::shape::relation
{
	bool Shape2D::IsOverlapping(const Shape2D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Shape2D::IsEnveloping(const Shape2D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Shape2D::IsEnvelopedBy(const Shape2D& other) const
	{
		return other.IsEnveloping(*this);
	}

	void to_json(Json& j, const Shape2D& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}