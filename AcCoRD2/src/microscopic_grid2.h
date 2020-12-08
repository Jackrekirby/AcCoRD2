#pragma once
#include "pch.h"

#include "microscopic_subvolume2.h"
#include "relation_box.h"

#include "vec3d.h"
#include "vec3i.h"

#include "molecule_destination.h"

#include "microscopic_owner.h"
#include "microscopic_surface.h"

#include "microscopic_relative.h"
#include "microscopic_relationship.h"
//#include "microscopic_high_priority_relative.h"
//#include "microscopic_low_priority_relative.h"
//#include "microscopic_neighbour.h"

// the global region must have a reflective or absorbing surface and by default should have 1 cell.
// a surface of type non can be drawn as having no outline, just a face colour
// would require RegionPlotter to adapt Shape Classes
// need to research &&
// why store absolute time per recent molecule?

// Definitions
// External : an object not owned by the same parent object
// Local : an object which holds a given molecule type and owned by same parent object
// Sibling : an object which holds the same molecule type and owned by same parent object


namespace accord::microscopic
{
	// an Owner is class which can own molecules, which includes Grid or Adsorbing Surfaces
	class Region2;

	class Grid2 : public Owner, public Relative
	{
	public:
		Grid2(Vec3d origin, Vec3d length, Vec3i n_subvolumes, double diffision_coefficient, MoleculeID id, Region2* region);

		void AddMolecule(const Vec3d& position);

		void AddMolecule(const Vec3d& position, double time);

		void DiffuseMolecules();

		std::optional<MoleculeDestination> CheckMoleculePath(const Vec3d& origin, const Vec3d& end);

		// dont change old position, create new one.
		Vec3d DiffuseMolecule(const NormalMolecule& molecule);

		// will require envionment time to be updated before event is finished or do environment time + time step
		Vec3d DiffuseMolecule(const RecentMolecule& molecule);

		// may need const version
		Region2& GetRegion();

		// may need const version
		std::vector<Subvolume2>& GetSubvolumes();

		// could be private?
		// may need const version
		// will always return a valid subvolume even if index is for a position outside of subvolume
		Subvolume2& GetSubvolume(Vec3i index);

		// could be private?
		// if index is not valid null will be returned
		Subvolume2* GetSubvolumeIfExists(const Vec3i& index);

		// could be const if you are only linking local subvolumes and not vice versa
		// would be more efficient to do both at same time. Would then require a check to see if regions are already
		// neighbours. Grid is of same molecule type
		void LinkGrid(Grid2& grid);

		// Local grids (excluding itself) only need a one way connection while external need a two way connection
		// every cell needs to be checked for overlap due to different cell sizes.
		void LinkLocalGrid(Grid2& grid);

		MoleculeID GetMoleculeID();

		void AddNeighbour(Relative* relative, SurfaceType type);

		void AddLowPriorityRelative(Relative* relative, SurfaceType type);

		void AddHighPriorityRelative(Relative* relative, SurfaceType type);

		// Inherited Class Functions

		const SurfaceShape& GetShape() const;

		SurfaceType GetDefaultSurfaceType() const;

		// may be able to merge these pass functions
		std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid2* owner,
			SurfaceType surface_type);

	private:
		// need to change to NeighbourAndSurfaceType ...
		// consider changing GetSurface to GetShape due to confusion of Surface.GetSurface
		// also Surface.GetType() no longer required

		// surface direction will be the same for all relatives
		// need to know the direction of a surfaces for high priority relatives
		// high prioity = external collision check or either surface side
		// as low priority or neighbour only is on border check required, no direction

		// neighbour.checkcollision called external for regions and gets direction for surfaces

		std::vector<Relationship> neighbour_relationships; // can be grids, mesoregion or adsorbing surfaces
		std::vector<Relationship> low_priority_relationships; // can be grids or mesoregions
		std::vector<Relationship> high_priority_relationships; // cans be grids, mesoregions or surfaces

		MoleculeID id;
		Region2* region; // regions which owns this grid
		Vec3i n_subvolumes;
		shape::relation::Box box;
		double diffision_coefficient;
		std::vector<Subvolume2> subvolumes;
		
		// create subvolumes upon class construction
		void CreateSubvolumes();

		// go through each subvolume of the same molecule type
		void LinkSiblingSubvolumes();

		// for a given cell check the 26 cells surrounding it and link them if they are not already linked
		void LinkSiblingSubvolumes(const Vec3i& i);
	};
}