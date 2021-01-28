#pragma once
#include "microscopic_relative2.h"
namespace accord::microscopic
{
	class NeighbourRelativeShape;

	class NeighbourRelative : public Relative2
	{
	public:
		virtual const NeighbourRelativeShape& GetShape() const = 0;
	};
}