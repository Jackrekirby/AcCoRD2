// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"

#include "vec1d.h"

namespace accord::Vec1d
{
	// intersection = origin + time * (end - origin)
	double Lerp(double origin, double end, double time)
	{
		return origin + time * (end - origin);
	}

	// time = (intersection - origin) / (end - origin);
	double InverseLerp(double origin, double end, double intersection)
	{
		return (intersection - origin) / (end - origin);
	}

	// mirrored_position = (2 * mirror_line - position);
	double MirrorPosition(double position, double mirror_line)
	{
		return (2 * mirror_line - position);
	}

	double Square(double a)
	{
		return a * a;
	}

	double Cube(double a)
	{
		return a * a * a;
	}

	double Vec1d::Min(double a, double b)
	{
		return { (a < b) ? a : b };
	}

	double Vec1d::Max(double a, double b)
	{
		return { (a > b) ? a : b };
	}
}