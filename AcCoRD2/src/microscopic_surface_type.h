// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::microscopic
{
	enum class SurfaceType
	{
		Absorbing, Adsorbing, Membrane, Reflecting, None
	};

	void from_json(const Json& j, SurfaceType& surface_type);
}