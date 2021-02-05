#pragma once
#include "pch.h"

namespace accord
{
	struct Vec3d;
	namespace shape::relation
	{
		class Box;
	}

	class PassiveActorShape
	{
	public:
		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		virtual bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const = 0;

		virtual bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const PassiveActorShape& shape);
}