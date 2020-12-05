#include "pch.h"
#include "microscopic_region2.h"

#include "environment.h"

#include "microscopic_neighbour.h"
#include "microscopic_low_priority_relation.h"
#include "microscopic_high_priority_relation.h"
#include "microscopic_surface_shape.h"

namespace accord::microscopic
{
	Region2::Region2(std::vector<double> diffision_coefficients,
		std::vector<Vec3i> n_subvolumes_per_grid, std::unique_ptr<Surface> surface,
		double start_time, double time_step, int priority, EventQueue* event_queue,
		RegionID id)
		: surface(std::move(surface)), Event(start_time, priority, event_queue),
		time_step(time_step), id(id)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid);
	}

	void Region2::Run()
	{
		// zeroth order reactions
		// first order reactions
		for (auto& grid : grids)
		{
			grid.DiffuseMolecules();
		}
		// second order reactions
		UpdateTime(GetNextEventTime());
	}

	// add neighbour relationship between local and external grids of same molecule type.
	// will need a seperate add neighbour for surfaces or pass neighbour directly into here
	void Region2::AddNeighbour(Region2& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddNeighbour(static_cast<Neighbour*>(&region.GetGrid(id)));
		}
	}

	void Region2::AddHighPriorityRelative(Region2& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddHighPriorityRelation(static_cast<HighPriorityRelation*>(&region.GetGrid(id)));
		}
	}

	void Region2::AddLowPriorityRelative(Region2& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddLowPriorityRelation(static_cast<LowPriorityRelation*>(&region.GetGrid(id)));
		}
	}

	// add a recent molecule
	void Region2::AddMolecule(MoleculeID id, const Vec3d& position, double time)
	{
		GetGrid(id).AddMolecule(position, time);
	}

	// add a normal molecule
	void Region2::AddMolecule(MoleculeID id, const Vec3d& position)
	{
		GetGrid(id).AddMolecule(position);
	}

	// reaction classes can always internally get and pass a Grid to the reaction class constructor.
	// Zeroth Order Reaction
	void Region2::AddReaction(const MoleculeIDs& products)
	{
		zeroth_order_reactions.emplace_back(products);
	}

	// First Order Reaction
	void Region2::AddReaction(MoleculeID reactant, const MoleculeIDs& products)
	{
		first_order_reactions.emplace_back(reactant, products);
	}

	// Second Order Reaction (if reactant_a == reactant_b then construct single reactant class)
	void Region2::AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products)
	{
		second_order_reactions.AddReaction(reactant_a, reactant_b, products);
	}

	// returns event time + time_step
	double Region2::GetNextEventTime()
	{
		return GetTime() + GetTimeStep();
	}

	// returns time_step
	double Region2::GetTimeStep()
	{
		return time_step;
	}

	// may need to add const versions of GetGrid(s)
	std::vector<Grid2>& Region2::GetGrids()
	{
		return grids;
	}

	Grid2& Region2::GetGrid(MoleculeID id)
	{
		return grids.at(id);
	}

	void Region2::GenerateGrids(std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes_per_grid)
	{
		shape::basic::Box b = surface->GetShape().GenerateBoundingBox();
		for (int i = 0; i < Environment::GetNumberOfMoleculeTypes(); i++)
		{
			grids.emplace_back(b.GetOrigin(), b.GetLength(), 
				n_subvolumes_per_grid.at(i), diffision_coefficients.at(i), i, this);
		}
	}

	
	void Region2::LinkGrids()
	{
		for (auto g1 = grids.begin(); g1 != grids.end(); ++g1)
		{
			// ignore unintended copy warning for g2 = g1
			for (auto g2 = g1; g2 != grids.end(); ++g2)
			{
				g1->LinkGrid(*g2);
			}
		}
	}

	// where is grid overlap being checked (in the link functions or prior?)
	// they are called by relationship functions
	void Region2::LinkGrids(Region2& region, const MoleculeIDs& ids)
	{
		// link each molecule type to every other molecule type
		// could be more efficient by only linking molecule types where a reaction can occur between them
		for (auto& id1 : ids)
		{
			for (auto& id2 : ids)
			{
				GetGrid(id1).LinkGrid(region.GetGrid(id2));
			}
		}
	}

	Surface& Region2::GetSurface()
	{
		return *surface;
	}

	RegionID Region2::GetID() const
	{
		return id;
	}

	Event::Type Region2::GetType() const
	{
		return Event::Type::microscopic_region;
	}
}