#pragma once
#include "vec3d.h"

namespace accord::microscopic
{
	class Owner;

	class MoleculeDestination
	{
	public:
		MoleculeDestination(Vec3d position, Owner* owner);

		const Vec3d& GetPosition() const;

		Owner& GetOwner() const;
	private:
		Vec3d position;
		Owner* owner;
	};
}
