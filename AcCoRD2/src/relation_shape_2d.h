// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::shape::relation
{
	class Rect;
	class Circle;

	class Shape2D
	{
	public:
		Shape2D() = default;

		virtual bool IsOverlapping(const Rect& other) const = 0;

		virtual bool IsEnveloping(const Rect& other) const = 0;

		virtual bool IsEnvelopedBy(const Rect& other) const = 0;

		virtual bool IsOverlapping(const Circle& other) const = 0;

		virtual bool IsEnveloping(const Circle& other) const = 0;

		virtual bool IsEnvelopedBy(const Circle& other) const = 0;

		virtual bool IsOverlapping(const Shape2D& other) const = 0;

		virtual bool IsEnveloping(const Shape2D& other) const = 0;

		virtual bool IsEnvelopedBy(const Shape2D& other) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape2D& surface_shape);
}