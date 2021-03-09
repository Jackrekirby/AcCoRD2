// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "basic_rect.h"
#include "vec2b.h"

namespace accord::shape::basic
{
	Rect::Rect(Vec2d origin, Vec2d length)
		: origin(origin), length(length), end(origin + length)
	{

	}

	void Rect::Move(const Vec2d& origin)
	{
		this->origin = origin;
		this->end = origin + length;
	}

	void Rect::Resize(const Vec2d& length)
	{
		this->length = length;
		this->end = origin + length;
	}

	const Vec2d& Rect::GetOrigin() const
	{
		return origin;
	}

	const Vec2d& Rect::GetEnd() const
	{
		return end;
	}

	const Vec2d& Rect::GetLength() const
	{
		return length;
	}

	Vec2d Rect::CalculateCentre() const
	{
		return origin + 0.5 * length;
	}

	double Rect::CalculateArea() const
	{
		return length.Area();
	}

	bool Rect::IsWithinBorder(const Vec2d& position) const
	{
		return ((position > GetOrigin()).All() && (position < GetEnd()).All());
	}

	bool Rect::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return ((position >= GetOrigin()).All() && (position <= GetEnd()).All());
	}

	bool Rect::IsOnBorder(const Vec2d& position) const
	{
		return ((position == GetOrigin()) || (position == GetEnd())).All();
	}
	
	void Rect::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Rect& rect)
	{
		j["type"] = "rect";
		j["origin"] = rect.GetOrigin();
		j["length"] = rect.GetLength();
		j["end"] = rect.GetEnd();
	}
}