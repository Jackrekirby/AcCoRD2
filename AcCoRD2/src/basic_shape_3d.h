// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	class Box;

	// all basic 3D shapes must be able to generate a bounding box around them
	// and be able to calculate their volume
	class Shape3D : public Shape
	{
	public:
		virtual Box GenerateBoundingBox() const = 0;

		virtual double CalculateVolume() const = 0;
	};
}