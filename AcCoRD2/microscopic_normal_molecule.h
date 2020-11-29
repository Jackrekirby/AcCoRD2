#pragma once
#include "vec3d.h"

namespace accord::microscopic
{
	class NormalMolecule
	{
	public:
		NormalMolecule(Vec3d position);

		const Vec3d& GetPosition();
	private:
		Vec3d position;
	};
}
