#pragma once
#include "microscopic_relative2.h"
namespace accord::microscopic
{
	class HighPriorityRelativeShape;

	class HighPriorityRelative : public Relative2
	{
	public:
		enum class SurfaceDirection
		{
			Internal, External, Both
		};

		virtual const SurfaceDirection& GetSurfaceDirection() const = 0;

		virtual const HighPriorityRelativeShape& GetShape() const = 0;
	};

	void from_json(const Json& j, HighPriorityRelative::SurfaceDirection& surface_direction);
}