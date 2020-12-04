#include "pch.h"
#include "microscopic_surface.h"
#include "microscopic_surface_shape.h"

namespace accord::microscopic
{
	Surface::Surface(Type type)
		: type(type)
	{

	}

	Surface::Type Surface::GetType() const
	{
		return type;
	}
}