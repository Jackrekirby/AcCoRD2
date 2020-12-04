#pragma once
#include "microscopic_normal_molecule.h"

namespace accord::microscopic
{
	class RecentMolecule : public NormalMolecule
	{
	public:
		RecentMolecule(Vec3d position, double time);

		double GetTime() const;
	private:
		double time;
	};
}
