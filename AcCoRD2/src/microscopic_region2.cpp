#include "pch.h"
#include "microscopic_region2.h"

#include "environment.h"

#include "microscopic_neighbour.h"
#include "microscopic_low_priority_relation.h"
#include "microscopic_high_priority_relation.h"
#include "microscopic_surface_shape.h"

namespace accord::microscopic
{
	Region::Region(std::vector<double> diffision_coefficients,
		std::vector<Vec3i> n_subvolumes_per_grid,
		double start_time, double time_step, int priority,
		SurfaceType surface_type, MicroRegionID id)
		: Event5(start_time + time_step, priority),
		time_step(time_step), id(id), surface_type(surface_type), start_time(start_time),
		local_time(start_time)
	{
		
	}

	void Region::Run()
	{
		// zeroth order reactions
		for (auto& reaction : zeroth_order_reactions)
		{
			reaction.Run();
		}
		// first order reactions
		for (auto& reaction : first_order_reactions)
		{
			reaction.Run();
		}
		//diffuse molecules
		for (auto& grid : grids)
		{
			grid.DiffuseMolecules();
		}

		// update region time
		local_time = Environment::GetTime();

		// second order reactions
		// is a second order reactions class necessary as could just have one and two reactants types stored directly
		// or should zeroth and first order reactions be put into a class? e.g. to pass similar variables?
		for (auto& reaction : one_reactant_second_order_reactions)
		{
			reaction.CalculateReactions(local_time);
		}

		for (auto& reaction : two_reactant_second_order_reactions)
		{
			reaction.CalculateReactions(local_time);
		}

		// set time of next event
		SetEventTime(GetNextEventTime());
	}

	// add neighbour relationship between local and external grids of same molecule type.
	// will need a seperate add neighbour for surfaces or pass neighbour directly into here
	void Region::AddNeighbour(Region& region, SurfaceType type, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddNeighbour(static_cast<Relative*>(&region.GetGrid(id)), type);
		}
	}

	void Region::AddHighPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddHighPriorityRelative(static_cast<Relative*>(&region.GetGrid(id)), type);
		}
	}

	void Region::AddLowPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddLowPriorityRelative(static_cast<Relative*>(&region.GetGrid(id)), type);
		}
	}

	// add a recent molecule
	void Region::AddMolecule(MoleculeID id, const Vec3d& position, double time)
	{
		GetGrid(id).AddMolecule(position, time);
	}

	// add a normal molecule
	void Region::AddMolecule(MoleculeID id, const Vec3d& position)
	{
		GetGrid(id).AddMolecule(position);
	}

	void Region::AddMolecule(MoleculeID id, double time)
	{
		GetGrid(id).AddMolecule(time);
	}

	void Region::AddMolecule(MoleculeID id)
	{
		GetGrid(id).AddMolecule();
	}

	// reaction classes can always internally get and pass a Grid to the reaction class constructor.
	// Zeroth Order Reaction
	void Region::AddZerothOrderReaction(const MoleculeIDs& products, double reaction_rate)
	{
		zeroth_order_reactions.emplace_back(products, reaction_rate, this);
	}

	// First Order Reaction
	void Region::AddFirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, double total_reaction_rate)
	{
		first_order_reactions.emplace_back(reactant, products, reaction_rate, total_reaction_rate, this);
	}

	// Second Order Reaction (if reactant_a == reactant_b then construct single reactant class)
	void Region::AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
		const MoleculeIDs& products, double binding_radius, double unbinding_radius)
	{
		two_reactant_second_order_reactions.emplace_back(reactant_a, reactant_b, products, binding_radius, unbinding_radius, this);
	}

	void Region::AddSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products,
		double binding_radius, double unbinding_radius)
	{
		one_reactant_second_order_reactions.emplace_back(reactant, products, binding_radius, unbinding_radius, this);
	}

	// returns event time + time_step
	double Region::GetNextEventTime() const
	{
		return GetEventTime() + GetTimeStep();
	}

	// returns time_step
	double Region::GetTimeStep() const
	{
		return time_step;
	}

	double Region::GetStartTime() const
	{
		return start_time;
	}

	double Region::GetLocalTime() const
	{
		return local_time;
	}

	// may need to add const versions of GetGrid(s)
	std::vector<Grid>& Region::GetGrids()
	{
		return grids;
	}

	Grid& Region::GetGrid(MoleculeID id)
	{
		return grids.at(id);
	}

	void Region::GenerateGrids(std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes_per_grid)
	{
		//LOG_INFO("generating grid");
		grids.reserve(Environment::GetNumberOfMoleculeTypes());
		shape::basic::Box b = GetShape().GetBasicShape().GenerateBoundingBox();
		for (int i = 0; i < Environment::GetNumberOfMoleculeTypes(); i++)
		{
			grids.emplace_back(b.GetOrigin(), b.GetLength(), 
				n_subvolumes_per_grid.at(i), diffision_coefficients.at(i), i, this);
		}
	}

	void Region::LinkGrids()
	{
		for (auto g1 = grids.begin(); g1 != grids.end(); ++g1)
		{
			// ignore unintended copy warning for g2 = g1
			for (auto g2 = g1 + 1; g2 != grids.end(); ++g2)
			{
				//LOG_INFO("Linking {} to {}", g1->GetMoleculeID(), g2->GetMoleculeID());
				g1->LinkGrid(*g2);
			}
		}
	}

	// where is grid overlap being checked (in the link functions or prior?)
	// they are called by relationship functions
	void Region::LinkGrids(Region& region, const MoleculeIDs& ids)
	{
		//LOG_INFO(" {} {} ", GetID(), region.GetID());
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

	MicroRegionID Region::GetID() const
	{
		return id;
	}

	Event5::Type Region::GetType() const
	{
		return Event5::Type::microscopic_region;
	}

	SurfaceType Region::GetSurfaceType() const
	{
		return surface_type;
	}

	void Region::NextRealisation()
	{
		SetEventTime(start_time);
		for (auto& grid : grids)
		{
			for (auto& subvolume : grid.GetSubvolumes())
			{
				subvolume.GetNormalMolecules().clear();
				subvolume.GetRecentMolecules().clear();
			}
			for (auto& reaction : zeroth_order_reactions)
			{
				reaction.NextRealisation();
			}
		}
	}
}