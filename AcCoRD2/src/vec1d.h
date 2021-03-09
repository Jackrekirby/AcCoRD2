// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::Vec1d
{
	// intersection = origin + time * (end - origin)
	double Lerp(double origin, double end, double time);

	// time = (intersection - origin) / (end - origin);
	double InverseLerp(double origin, double end, double intersection);

	// mirrored_position = (2 * mirror_line - position);
	double MirrorPosition(double a, double mirror_line);

	double Square(double a);

	double Cube(double a);

	double Min(double a, double b);

	double Max(double a, double b);
}

