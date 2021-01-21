#pragma once

namespace accord::microscopic
{
	enum class SurfaceType
	{
		Absorbing, Adsorbing, Membrane, Reflecting, None
	};

	void from_json(const Json& j, SurfaceType& surface_type);
}