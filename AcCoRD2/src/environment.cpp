#include "pch.h"
#include "environment.h"
#include <filesystem>
#include "reaction_manager.h"

namespace accord
{
	void Environment::Init(std::string simulation_name, int num_realisations, 
		double run_time, int num_molecule_types, int num_microscopic_regions,
		uint64_t seed)
	{
		Environment::time = 0;
		Environment::run_time = run_time;
		Environment::num_molecule_types = num_molecule_types;
		Environment::microscopic_regions.reserve(num_microscopic_regions);
		Environment::simulation_name = simulation_name;
		Environment::num_realisations = num_realisations;
		Environment::current_realisation = 0;
		Environment::seed = seed;

		Random::SetSeed(seed);

		// will fail if files are open
		std::filesystem::remove_all(simulation_name +
			"/s" + std::to_string(Environment::seed));

		Environment::CreateDirectories();

		ReactionManager::Init(num_molecule_types);
	}

	void Environment::SetTime(double time)
	{
		Environment::time = time;
	}

	double Environment::GetTime()
	{
		return time;
	}

	double Environment::GetRunTime()
	{
		return run_time;
	}

	int Environment::GetNumberOfMoleculeTypes()
	{
		return num_molecule_types;
	}

	MoleculeIDs Environment::GetMoleculeIDs()
	{
		MoleculeIDs ids;
		ids.reserve(num_molecule_types);
		for (int i = 0; i < num_molecule_types; i++)
		{
			ids.emplace_back(i);
		}
		return ids;
	}

	void Environment::LinkReactionsToRegions()
	{
		for (auto& reaction : ReactionManager::GetZerothOrderReactions())
		{
			for (auto& region : reaction.GetRegions())
			{
				GetRegion(region).AddZerothOrderReaction(reaction.GetProducts(), reaction.GetRate());
			}
		}

		for (auto& reaction : ReactionManager::GetFirstOrderReactions())
		{
			for (auto& region : reaction.GetRegions())
			{
				GetRegion(region).AddFirstOrderReaction(reaction.GetReactant(), reaction.GetProducts(),
					reaction.GetRate(), reaction.GetTotalRate());
			}
		}

		for (auto& reaction : ReactionManager::GetSecondOrderReactions())
		{
			for (auto& region : reaction.GetRegions())
			{
				if (reaction.GetReactantA() == reaction.GetReactantB())
				{
					GetRegion(region).AddSecondOrderReaction(reaction.GetReactantA(), reaction.GetProducts(),
						reaction.GetBindingRadius(), reaction.GetUnBindingRadius());
				}
				else
				{
					GetRegion(region).AddSecondOrderReaction(reaction.GetReactantA(), reaction.GetReactantB(), reaction.GetProducts(),
						reaction.GetBindingRadius(), reaction.GetUnBindingRadius());
				}
			}
		}
	}

	std::string Environment::GetSimulationName()
	{
		return simulation_name;
	}

	int Environment::GetRealisationNumber()
	{
		return current_realisation;
	}

	microscopic::Region& Environment::GetRegion(RegionID id)
	{
		return *microscopic_regions.at(id);
	}

	std::vector<std::unique_ptr<microscopic::Region>>& Environment::GetRegions()
	{
		return microscopic_regions;
	}

	std::vector<std::unique_ptr<PassiveActor>>& Environment::GetPassiveActors()
	{
		return passive_actors;
	}

	std::string Environment::GetFilePath()
	{
		return Environment::GetSimulationName() +
			"/s" + std::to_string(Environment::seed) +
			"/r" + std::to_string(Environment::current_realisation) +
			"/";
	}

	// returns true if there is another relisation
	bool Environment::NextRealisation()
	{
		current_realisation++;
		if (current_realisation < num_realisations)
		{
			// clear molecules from all regions
			// clear event list
			// set all event times back to start time (thus start time needs to be saved)
			time = 0;
			Environment::CreateDirectories();
			return true;
		}
		else
		{
			return false;
		}
	}

	void Environment::CreateDirectories()
	{
		std::filesystem::create_directories(GetFilePath());
	}

	
	// the only type of relationship which does not need to be defined is a neighbour and none
	// if region a has a reflective surface and b is the neighbour
	void Environment::DefineRelationship(RegionID region_a, RegionID region_b, 
		RelationshipPriority priority, 
		SurfaceType ab_surface, SurfaceType ba_surface)
	{
		switch (priority)
		{
		case RelationshipPriority::A:
			GetRegion(region_a).AddLowPriorityRelative(GetRegion(region_b), ab_surface, GetMoleculeIDs());
			GetRegion(region_b).AddHighPriorityRelative(GetRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		case RelationshipPriority::B:
			GetRegion(region_a).AddHighPriorityRelative(GetRegion(region_b), ab_surface, GetMoleculeIDs());
			GetRegion(region_b).AddLowPriorityRelative(GetRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		case RelationshipPriority::None:
			GetRegion(region_a).AddNeighbour(GetRegion(region_b), ab_surface, GetMoleculeIDs());
			GetRegion(region_b).AddNeighbour(GetRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		default:
			LOG_CRITICAL("Unknown RelationshipPriority type");
			throw std::exception();
		}

		if (ab_surface == SurfaceType::None && ba_surface == SurfaceType::None)
		{
			GetRegion(region_a).LinkGrids(GetRegion(region_b), GetMoleculeIDs());
			GetRegion(region_a).LinkGrids(GetRegion(region_b), GetMoleculeIDs());
		}
	}

	void Environment::DefineRelationship(RegionID region_a, RegionID region_b, 
		RelationshipPriority priority, microscopic::SurfaceType surface)
	{
		DefineRelationship(region_a, region_b, priority, surface, surface);
	}

	void Environment::DefineRelationship(RegionID region_a, RegionID region_b, 
		RelationshipPriority priority,
		SurfaceTypes ab_surfaces, SurfaceTypes ba_surfaces)
	{
		int i = 0;
		switch (priority)
		{
		case RelationshipPriority::A:
			for (auto& ab_surface : ab_surfaces)
			{
				GetRegion(region_a).AddLowPriorityRelative(GetRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetRegion(region_b).AddHighPriorityRelative(GetRegion(region_a), ba_surface, { i });
				i++;
			}
			break;
		case RelationshipPriority::B:
			for (auto& ab_surface : ab_surfaces)
			{
				GetRegion(region_a).AddHighPriorityRelative(GetRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetRegion(region_b).AddLowPriorityRelative(GetRegion(region_a), ba_surface, { i });
				i++;
			}
			break;
		case RelationshipPriority::None:
			for (auto& ab_surface : ab_surfaces)
			{
				GetRegion(region_a).AddNeighbour(GetRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetRegion(region_b).AddNeighbour(GetRegion(region_a), ba_surface, { i });
				i++;
			}
			break;
		default:
			LOG_CRITICAL("Unknown RelationshipPriority type");
			throw std::exception();
		}

		for (int i = 0; i < num_molecule_types; i++)
		{
			if (ab_surfaces.at(i) == SurfaceType::None && ba_surfaces.at(i) == SurfaceType::None)
			{
				GetRegion(region_a).LinkGrids(GetRegion(region_b), {i});
				GetRegion(region_a).LinkGrids(GetRegion(region_b), {i});
			}
		}
	}

	void Environment::DefineRelationship(RegionID region_a, RegionID region_b, 
		RelationshipPriority priority, SurfaceTypes surfaces)
	{
		DefineRelationship(region_a, region_b, priority, surfaces, surfaces);
	}

	std::vector<std::unique_ptr<microscopic::Region>> Environment::microscopic_regions;
	std::vector<std::unique_ptr<PassiveActor>> Environment::passive_actors;
	double Environment::run_time = 0;
	double Environment::time = 0;
	int Environment::num_molecule_types = 0;
	std::string Environment::simulation_name = "simulation";
	int Environment::num_realisations = 1;
	int Environment::current_realisation = 0;
	uint64_t Environment::seed = 1;
}