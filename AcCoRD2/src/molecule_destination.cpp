#include "molecule_destination.h"
#include "pch.h"

namespace accord::microscopic
{
	MoleculeDestination::MoleculeDestination(Vec3d position, Owner* owner)
		: position(position), owner(owner)
	{

	}

	const Vec3d& MoleculeDestination::GetPosition() const
	{
		return position;
	}

	Owner& const MoleculeDestination::GetOwner() const
	{
		return *owner;
	}
}