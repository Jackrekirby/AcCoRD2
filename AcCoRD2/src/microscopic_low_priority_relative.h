#pragma once
#include "microscopic_relative2.h"
namespace accord::microscopic
{
	class LowPriorityRelativeShape;

	class LowPriorityRelative : public Relative2
	{
	public:
		virtual const LowPriorityRelativeShape& GetShape() const = 0;
	};
}