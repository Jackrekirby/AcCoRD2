#pragma once
#include "microscopic_relative.h"
namespace accord::microscopic
{
	class NeighbourRelativeShape;

	class NeighbourRelative : public Relative
	{
	public:
		virtual const NeighbourRelativeShape& GetShape() const = 0;

		virtual bool IsRegion() const = 0;
	};
}