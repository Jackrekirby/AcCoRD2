#pragma once

// can be a mesoregion, grid or adsorbing surface
// time not needed by meso but can just ignore it
namespace accord::microscopic
{
	struct Vec3d;

	class Owner
	{
		virtual void AddMolecule(const Vec3d& position, double time) = 0;
	};
}