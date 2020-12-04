#pragma once
#include "microscopic_owner.h"
#include "vec3d.h"

namespace accord::microscopic
{
	class MoleculeDestination
	{
	public:
		MoleculeDestination(Vec3d position, Owner* owner);

		const Vec3d& GetPosition() const;

		Owner& const GetOwner() const;
	private:
		Vec3d position;
		Owner* owner;
	};
}
