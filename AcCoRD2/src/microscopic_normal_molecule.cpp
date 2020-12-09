#include "pch.h"
#include "microscopic_normal_molecule.h"

namespace accord::microscopic
{
	NormalMolecule::NormalMolecule(Vec3d position)
		: position(position)
	{
		if (isnan(position.x))
		{
			LOG_CRITICAL(position);
			throw std::exception();
		}
		
		
	}

	const Vec3d& NormalMolecule::GetPosition() const
	{
		return position;
	}
}
