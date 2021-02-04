#include "pch.h"
#include "microscopic_region.h"

#include "environment.h"

//#include "microscopic_neighbour.h"
//#include "microscopic_low_priority_relation.h"
//#include "microscopic_high_priority_relation.h"
#include "microscopic_region_shape.h"
#include "microscopic_surface.h"
#include "mesoscopic_region.h"

namespace accord::microscopic
{
	// could remove const std::vector<SurfaceType> surface_type from constructor as passed straight to generate grids
	Region::Region(double time_step, int priority, const MicroscopicRegionID& id)
		: Event(time_step, priority), time_step(time_step), id(id), local_time(0)
	{
		
	}

	void Region::Run()
	{
		//LOG_INFO("Run");
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
			GetGrid(id).AddRelative(static_cast<NeighbourRelative*>(&region.GetGrid(id)), type);
		}
	}

	void Region::AddHighPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddRelative(static_cast<HighPriorityRelative*>(&region.GetGrid(id)), type);
		}
	}

	void Region::AddLowPriorityRelative(Region& region, SurfaceType type, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddRelative(static_cast<LowPriorityRelative*>(&region.GetGrid(id)), type);
		}
	}

	void Region::AddHighPrioritySurface(Surface& surface, const std::vector<SurfaceType>& types)
	{
		int i = 0;
		for (auto& grid : grids)
		{
			if (types.at(i) != SurfaceType::None)
			{
				grid.AddRelative(static_cast<HighPriorityRelative*>(&surface), types.at(i));
			}
			i++;
		}
	}

	void Region::AddNeighbourSurface(Surface& surface, const std::vector<SurfaceType>& types)
	{
		int i = 0;
		for (auto& grid : grids)
		{
			if (types.at(i) != SurfaceType::None)
			{
				grid.AddRelative(static_cast<NeighbourRelative*>(&surface), types.at(i));
			}
			i++;
		}
	}

	void Region::AddNeighbour(mesoscopic::Region& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddRelative(static_cast<NeighbourRelative*>(&region), SurfaceType::None);
		}
	}

	void Region::AddHighPriorityRelative(mesoscopic::Region& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddRelative(static_cast<HighPriorityRelative*>(&region), SurfaceType::None);
		}
	}

	void Region::AddLowPriorityRelative(mesoscopic::Region& region, const MoleculeIDs& ids)
	{
		for (auto& id : ids)
		{
			GetGrid(id).AddRelative(static_cast<LowPriorityRelative*>(&region), SurfaceType::None);
		}
	}

	// add a recent molecule
	void Region::AddMolecule(const MoleculeID& id, const Vec3d& position, double time)
	{
		GetGrid(id).AddMolecule(position, time);
	}

	// add a normal molecule
	void Region::AddMolecule(const MoleculeID& id, const Vec3d& position)
	{
		GetGrid(id).AddMolecule(position);
	}

	void Region::AddMolecule(const MoleculeID& id, double time)
	{
		GetGrid(id).AddMolecule(time);
	}

	void Region::AddMolecule(const MoleculeID& id)
	{
		GetGrid(id).AddMolecule();
	}

	// reaction classes can always internally get and pass a Grid to the reaction class constructor.
	// Zeroth Order Reaction
	void Region::AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate)
	{
		zeroth_order_reactions.emplace_back(products, reaction_rate, this);
	}

	// First Order Reaction
	void Region::AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate, double total_reaction_rate)
	{
		first_order_reactions.emplace_back(reactant, products, reaction_rate, total_reaction_rate, this);
	}

	// Second Order Reaction (if reactant_a == reactant_b then construct single reactant class)
	void Region::AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
		const std::vector<int>& products, double binding_radius, double unbinding_radius)
	{
		two_reactant_second_order_reactions.emplace_back(reactant_a, reactant_b, products, binding_radius, unbinding_radius, this);
	}

	void Region::AddSecondOrderReaction(const MoleculeID& reactant, const std::vector<int>& products,
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

	double Region::GetLocalTime() const
	{
		return local_time;
	}

	// may need to add const versions of GetGrid(s)
	std::vector<Grid>& Region::GetGrids()
	{
		return grids;
	}

	Grid& Region::GetGrid(const MoleculeID& id)
	{
		return grids.at(id);
	}

	void Region::GenerateGrids(std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes_per_grid, const std::vector<SurfaceType>& surface_types)
	{
		//LOG_INFO("generating grid");
		grids.reserve(Environment::GetNumberOfMoleculeTypes());
		shape::basic::Box b = GetShape().GetBasicShape().GenerateBoundingBox();
		for (int i = 0; i < Environment::GetNumberOfMoleculeTypes(); i++)
		{
			grids.emplace_back(b.GetOrigin(), b.GetLength(), 
				n_subvolumes_per_grid.at(i), diffision_coefficients.at(i), surface_types.at(i), i, this);
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
				//g1->LinkGrid(*g2);
				g1->LinkCousinSubvolumes(*g2);
			}
		}
	}

	// where is grid overlap being checked (in the link functions or prior?)
	// they are called by relationship functions
	void Region::LinkGrids(Region& region, const MoleculeIDs& ids)
	{
		LOG_INFO("Linking Grids: {} {}", GetID(), region.GetID());
		for (auto& id1 : ids)
		{
			for (auto& id2 : ids)
			{
				
				GetGrid(id1).LinkGrid(region.GetGrid(id2));
			}
		}
	}

	MicroscopicRegionID Region::GetID() const
	{
		return id;
	}

	std::string Region::LogEvent() const
	{
		return fmt::format("Mesoscopic Region. ID:{}, Priority:{}, Time:{}", id, priority, time);
	}

	void Region::NextRealisation()
	{
		SetEventTime(0);
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