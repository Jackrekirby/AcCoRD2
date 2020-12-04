#pragma once
#include "vec3d.h"
// can be a mesoregion, grid or adsorbing surface
// time not needed by meso but can just ignore it
namespace accord::microscopic
{
	class Owner
	{
	public:
		virtual void AddMolecule(const Vec3d& position, double time) = 0;

		virtual void AddMolecule(const Vec3d& position) = 0;
	};
}