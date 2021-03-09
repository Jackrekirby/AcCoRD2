// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	void from_json(const Json& j, SurfaceType& surface_type)
	{
		std::string surface_str = j.get<std::string>();
		if (surface_str == "Absorbing")
		{
			surface_type = SurfaceType::Absorbing;
		}
		else if (surface_str == "Adsorbing")
		{
			surface_type = SurfaceType::Adsorbing;
		}
		else if (surface_str == "Membrane")
		{
			surface_type = SurfaceType::Membrane;
		}
		else if (surface_str == "Reflecting")
		{
			surface_type = SurfaceType::Reflecting;
		}
		else if (surface_str == "None")
		{
			surface_type = SurfaceType::None;
		}
	}
}