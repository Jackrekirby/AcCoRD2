#pragma once
#include "microscopic_relative.h"
namespace accord::microscopic
{
	class LowPriorityRelativeShape;

	class LowPriorityRelative : public Relative
	{
	public:
		virtual const LowPriorityRelativeShape& GetShape() const = 0;
	};
}