#pragma once
#include "pch.h"
#include "vec3d.h"
#include "event.h"
#include "microscopic_grid.h"
//#include "microscopic_surface.h"
#include "microscopic_zeroth_order_reaction.h"
#include "microscopic_first_order_reaction.h"
#include "microscopic_second_order_reaction.h"
#include "microscopic_relationship.h"
#include "microscopic_surface_shape.h"
#include "microscopic_surface_type.h"
#include "microscopic_region_id.h"
#include "molecule_id.h"
#include "microscopic_region_id.h"
// Surface(Shape3D shape, Enum surface_type) OR Surface : public shape, public absorbing (multiple inheritance)

namespace accord::microscopic
{
	class Region : public Event
	{
	public:
		Region(const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
			double time_step, int priority, SurfaceType surface_type, const MicroscopicRegionID& id);

		void Run();

		// add neighbour relationship between local and external grids of same molecule type.
		void AddNeighbour(Region& region, SurfaceType type, const MoleculeIDs& ids);

		void AddHighPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids);

		void AddLowPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids);

		// add a recent molecule
		void AddMolecule(const MoleculeID& id, const Vec3d& position, double time);

		// add a normal molecule
		void AddMolecule(const MoleculeID& id, const Vec3d& position);

		// add a recent molecule with a random position
		void AddMolecule(const MoleculeID& id, double time);

		// add a normal molecule with a random position
		void AddMolecule(const MoleculeID& id);

		// reaction classes can always internally get and pass a Grid to the reaction class constructor.
		// Zeroth Order Reaction
		void AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate);

		// First Order Reaction
		void AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate, double total_reaction_rate);

		// Second Order Reaction (if reactant_a == reactant_b then construct single reactant class)
		void AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b, const std::vector<int>& products,
			double binding_radius, double unbinding_radius);

		void AddSecondOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double binding_radius, double unbinding_radius);

		// returns environment time + time_step
		double GetNextEventTime() const;

		// returns time_step
		double GetTimeStep() const;

		// is 1 time step behind the current environment time
		double GetLocalTime() const;

		// may need to add const versions of GetGrid(s)
		std::vector<Grid>& GetGrids();

		Grid& GetGrid(const MoleculeID& id);

		std::string LogEvent() const;

		// each region type will have its own surface shape which is why GetSurface is virtual
		// may need const version of get surface

		virtual const SurfaceShape& GetShape() const = 0;

		SurfaceType GetSurfaceType() const;

		void NextRealisation();

		void LinkGrids(Region& region, const MoleculeIDs& ids);
	private:
		//std::unique_ptr<SurfaceShape> surface_shape;
		SurfaceType surface_type;

		std::vector<Grid> grids;
		// reactions will need to be passed pointer to region
		// e.g. zeroth order reaction needs to know the volume of the region
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		std::vector<OneReactantSecondOrderReaction> one_reactant_second_order_reactions;
		std::vector<TwoReactantSecondOrderReaction> two_reactant_second_order_reactions;
		double time_step;
		double local_time;
		MicroscopicRegionID id;

		// link local grids to external grids between each molecule type for bi-molecular reactions.
		// called by add relationship functions.
		// may wish to sperate function into neighbour, high priority and low priority linking for speed
		// (no need to check for overlap between subvolumes between neighbouring regions)
		

	protected:
		void GenerateGrids(std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes);

		// links local grids to eachother for bi-molecular reactions
		void LinkGrids();
	};
}