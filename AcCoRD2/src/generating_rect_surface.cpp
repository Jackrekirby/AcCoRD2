// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "generating_rect_surface.h"
#include "basic_rect_surface.h"

namespace accord::shape::generating
{
	RectSurface::RectSurface(Plane plane, Rect rect)
		: Surface(plane), rect(rect)
	{

	}

	RectSurface::RectSurface(const basic::RectSurface& rect_surface)
		: Surface(rect_surface.plane), rect(rect_surface.rect)
	{
	}

	const Rect& RectSurface::GetShape() const
	{
		return rect;
	}
}
