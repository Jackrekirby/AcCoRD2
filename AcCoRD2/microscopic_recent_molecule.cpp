#include "pch.h"
#include "microscopic_recent_molecule.h"

namespace accord::microscopic
{
	RecentMolecule::RecentMolecule(Vec3d position, double time)
		: NormalMolecule(position), time(time)
	{

	}

	double RecentMolecule::GetTime()
	{
		return time;
	}
}
