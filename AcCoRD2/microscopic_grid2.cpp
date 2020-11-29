#pragma once
#include "microscopic_grid2.h"

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

	Grid2::Grid2(Vec3d origin, Vec3d length, Vec3i n_subvolumes, double diffision_coefficient, Region2* region)
		: box(origin, length), n_subvolumes(n_subvolumes), diffision_coefficient(diffision_coefficient),
		region(region)
	{

	}

	void Grid2::AddMolecule(const Vec3d& position)
	{
	}

	void Grid2::AddMolecule(const Vec3d& position, double time)
	{
	}

	void Grid2::DiffuseMolecules()
	{
	}

	std::optional<MoleculeDestination> Grid2::CheckMoleculePath(const Vec3d& origin, const Vec3d& end)
	{
	}

	// dont change old position, create new one.
	Vec3d Grid2::DiffuseMolecule(const NormalMolecule& molecule)
	{
	}

	// will require envionment time to be updated before event is finished or do environment time + time step
	Vec3d Grid2::DiffuseMolecule(const RecentMolecule& molecule)
	{
	}

	// may need const version
	Region2& Grid2::GetRegion()
	{
	}

	// may need const version
	std::vector<Subvolume>& Grid2::GetSubvolumes()
	{
	}

	// could be private?
	// may need const version
	// will always return a valid subvolume even if index is for a position outside of subvolume
	Subvolume& Grid2::GetSubvolume(const Vec3i& index)
	{
	}

	// could be private?
	// if index is not valid null will be returned
	std::optional<Subvolume&> Grid2::GetSubvolumeIfExists(const Vec3i& index)
	{
	}

	// could be const if you are only linking local subvolumes and not vice versa
	// would be more efficient to do both at same time. Would then require a check to see if regions are already
	// neighbours. Grid is of same molecule type
	void Grid2::LinkGrid(Grid2& grid)
	{
	}

	// Local grids (excluding itself) only need a one way connection while external need a two way connection
	// every cell needs to be checked for overlap due to different cell sizes.
	void Grid2::LinkLocalGrid(Grid2& grid)
	{
	}

	MoleculeID Grid2::GetMoleculeID()
	{
	}

	// create subvolumes upon class construction
	void Grid2::CreateSubvolumes()
	{
	}

	// go through each subvolume of the same molecule type
	void Grid2::LinkSiblingSubvolumes()
	{
	}

	// for a given cell check the 26 cells surrounding it and link them if they are not already linked
	void Grid2::LinkSiblingSubvolumes(const Vec3i& i)
	{
	}
}