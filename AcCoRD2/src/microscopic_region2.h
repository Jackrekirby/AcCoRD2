#pragma once
#include "pch.h"
#include "vec3d.h"
#include "event.h"
#include "microscopic_grid2.h"
//#include "microscopic_surface.h"
#include "microscopic_zeroth_order_reaction.h"
#include "microscopic_first_order_reaction.h"
#include "microscopic_second_order_reaction.h"
#include "object_ids.h"
#include "microscopic_relationship.h"
#include "microscopic_surface_shape.h"
#include "microscopic_surface_type.h"
// Surface(Shape3D shape, Enum surface_type) OR Surface : public shape, public absorbing (multiple inheritance)

namespace accord::microscopic
{
	class Region2 : public Event
	{
	public:
		Region2(std::vector<double> diffision_coefficients,
			std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority, EventQueue* event_queue,
			SurfaceType surface_type, RegionID id);

		void Run();

		// add neighbour relationship between local and external grids of same molecule type.
		void AddNeighbour(Region2& region, SurfaceType type, const MoleculeIDs& ids);

		void AddHighPriorityRelative(Region2& region, SurfaceType type, const MoleculeIDs& ids);

		void AddLowPriorityRelative(Region2& region, SurfaceType type, const MoleculeIDs& ids);

		// add a recent molecule
		void AddMolecule(MoleculeID id, const Vec3d& position, double time);

		// add a normal molecule
		void AddMolecule(MoleculeID id, const Vec3d& position);

		// add a recent molecule with a random position
		void AddMolecule(MoleculeID id, double time);

		// add a normal molecule with a random position
		void AddMolecule(MoleculeID id);

		// reaction classes can always internally get and pass a Grid to the reaction class constructor.
		// Zeroth Order Reaction
		void AddReaction(const MoleculeIDs& products, double reaction_rate);

		// First Order Reaction
		void AddReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, double total_reaction_rate);

		// Second Order Reaction (if reactant_a == reactant_b then construct single reactant class)
		void AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products);

		// returns environment time + time_step
		double GetNextEventTime() const;

		// returns time_step
		double GetTimeStep() const;

		double GetStartTime() const;

		// is 1 time step behind the current environment time
		double GetLocalTime() const;

		// may need to add const versions of GetGrid(s)
		std::vector<Grid2>& GetGrids();

		Grid2& GetGrid(MoleculeID id);

		// each region type will have its own surface shape which is why GetSurface is virtual
		// may need const version of get surface

		Event::Type GetType() const;

		virtual const SurfaceShape& GetShape() const = 0;

		SurfaceType GetSurfaceType() const;

		RegionID GetID() const;

		void NextRealisation();
	private:
		//std::unique_ptr<SurfaceShape> surface_shape;
		SurfaceType surface_type;

		std::vector<Grid2> grids;
		// reactions will need to be passed pointer to region
		// e.g. zeroth order reaction needs to know the volume of the region
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		SecondOrderReactions second_order_reactions;
		double time_step;
		double start_time;
		double local_time;
		RegionID id;

		// links local grids to eachother for bi-molecular reactions
		void LinkGrids();

		// link local grids to external grids between each molecule type for bi-molecular reactions.
		// called by add relationship functions.
		// may wish to sperate function into neighbour, high priority and low priority linking for speed
		// (no need to check for overlap between subvolumes between neighbouring regions)
		void LinkGrids(Region2& region, const MoleculeIDs& ids);

	protected:
		void GenerateGrids(std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes);
	};
}