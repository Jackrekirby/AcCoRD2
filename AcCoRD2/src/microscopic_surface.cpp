#include "pch.h"
#include "microscopic_surface.h"

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