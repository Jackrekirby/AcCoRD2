#include "pch.h"
#include "environment.h"
#include <filesystem>
#include "reaction_manager.h"

#include "microscopic_box_region.h"
#include "microscopic_cylinder_region.h"
#include "microscopic_sphere_region.h"
#include "event_queue.h"

namespace accord
{
	void Environment::Init(std::string simulation_path, int num_realisations,
		double run_time, int num_molecule_types, int num_microscopic_regions,
		int num_mesoscopic_regions, int num_passive_actors, int num_active_actors, 
		uint64_t seed)
	{
		MoleculeID::SetNumIDs(num_molecule_types);
		MicroscopicRegionID::SetNumIDs(num_microscopic_regions);
		MesoscopicRegionID::SetNumIDs(num_mesoscopic_regions);
		PassiveActorID::SetNumIDs(num_passive_actors);
		ActiveActorID::SetNumIDs(num_active_actors);

		Environment::time = 0;
		Environment::run_time = run_time;
		Environment::num_molecule_types = num_molecule_types;
		Environment::microscopic_regions.reserve(num_microscopic_regions);
		Environment::mesoscopic_regions.reserve(num_mesoscopic_regions);
		Environment::passive_actors.reserve(num_passive_actors);
		Environment::active_actors.reserve(num_active_actors);
		Environment::simulation_path = simulation_path;
		Environment::num_realisations = num_realisations;
		Environment::current_realisation = 0;
		Environment::seed = seed;
		Environment::event_queue = EventQueue(num_microscopic_regions + 
			num_mesoscopic_regions + num_passive_actors + num_active_actors);

		Random::SetSeed(seed);

		// will fail if files are open
		std::filesystem::remove_all(simulation_path +
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
			for (auto& region : reaction.GetMicroscopicRegions())
			{
				GetMicroscopicRegion(region).AddZerothOrderReaction(reaction.GetProducts(), reaction.GetRate());
			}

			for (auto& region : reaction.GetMesoscopicRegions())
			{
				GetMesoscopicRegion(region).AddZerothOrderReaction(reaction.GetProducts(), reaction.GetRate());
			}
		}

		for (auto& reaction : ReactionManager::GetFirstOrderReactions())
		{
			for (auto& region : reaction.GetMicroscopicRegions())
			{
				GetMicroscopicRegion(region).AddFirstOrderReaction(reaction.GetReactant(), reaction.GetProducts(),
					reaction.GetRate(), reaction.GetTotalRate());
			}

			for (auto& region : reaction.GetMesoscopicRegions())
			{
				GetMesoscopicRegion(region).AddFirstOrderReaction(reaction.GetReactant(), reaction.GetProducts(), reaction.GetRate());
			}
		}

		for (auto& reaction : ReactionManager::GetSecondOrderReactions())
		{
			for (auto& region : reaction.GetMicroscopicRegions())
			{
				if (reaction.GetReactantA() == reaction.GetReactantB())
				{
					GetMicroscopicRegion(region).AddSecondOrderReaction(reaction.GetReactantA(), reaction.GetProducts(),
						reaction.GetBindingRadius(), reaction.GetUnBindingRadius());
				}
				else
				{
					GetMicroscopicRegion(region).AddSecondOrderReaction(reaction.GetReactantA(), reaction.GetReactantB(), reaction.GetProducts(),
						reaction.GetBindingRadius(), reaction.GetUnBindingRadius());
				}
			}

			for (auto& region : reaction.GetMesoscopicRegions())
			{
				GetMesoscopicRegion(region).AddSecondOrderReaction(reaction.GetReactantA(), reaction.GetReactantB(), reaction.GetProducts(), reaction.GetRate());
			}
		}
	}

	void Environment::AddRegion(shape::basic::Box box, SurfaceType surface_type, 
		const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
		double time_step, int priority)
	{
		GetRegions().emplace_back(std::make_unique<microscopic::BoxRegion>(
			box, diffision_coefficients, n_subvolumes, time_step, priority,
			surface_type, static_cast<int>(GetRegions().size())));
	}

	void Environment::AddRegion(shape::basic::Sphere sphere, SurfaceType surface_type, 
		const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
		double time_step, int priority)
	{
		GetRegions().emplace_back(std::make_unique<microscopic::SphereRegion>(
			sphere, diffision_coefficients, n_subvolumes, time_step, priority,
			surface_type, static_cast<int>(Environment::GetRegions().size())));
	}

	void Environment::AddRegion(shape::basic::Cylinder cylinder, SurfaceType surface_type, 
		const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
		double time_step, int priority)
	{
		GetRegions().emplace_back(std::make_unique<microscopic::CylinderRegion>(
			cylinder, diffision_coefficients, n_subvolumes, time_step, priority,
			surface_type, static_cast<int>(Environment::GetRegions().size())));
	}

	std::string Environment::GetSimulationPath()
	{
		return simulation_path;
	}

	int Environment::GetRealisationNumber()
	{
		return current_realisation;
	}



	microscopic::Region& Environment::GetMicroscopicRegion(const MicroscopicRegionID& id)
	{
		return *microscopic_regions.at(id);
	}

	std::vector<microscopic::Region*> Environment::GetRegions(const MicroscopicRegionIDs& ids)
	{
		std::vector<microscopic::Region*> regions_ptrs;
		for (auto id : ids)
		{
			regions_ptrs.push_back(microscopic_regions.at(id).get());
		}
		return regions_ptrs;
	}

	std::vector<std::unique_ptr<microscopic::Region>>& Environment::GetRegions()
	{
		return microscopic_regions;
	}



	mesoscopic::Region& Environment::GetMesoscopicRegion(const MesoscopicRegionID& id)
	{
		return mesoscopic_regions.at(id);
	}

	std::vector<mesoscopic::Region*> Environment::GetMesoscopicRegions(const MesoscopicRegionIDs& ids)
	{
		std::vector<mesoscopic::Region*> regions_ptrs;
		for (auto id : ids)
		{
			regions_ptrs.push_back(&mesoscopic_regions.at(id));
		}
		return regions_ptrs;
	}

	std::vector<mesoscopic::Region>& Environment::GetMesoscopicRegions()
	{
		return mesoscopic_regions;
	}


	std::vector<std::unique_ptr<PassiveActor>>& Environment::GetPassiveActors()
	{
		return passive_actors;
	}

	std::vector<std::unique_ptr<ActiveActor>>& Environment::GetActiveActors()
	{
		return active_actors;
	}

	std::string Environment::GetRealisationPath()
	{
		return Environment::GetSimulationPath() +
			"/s" + std::to_string(seed) +
			"/r" + std::to_string(current_realisation) + "/";
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
		std::filesystem::create_directories(GetRealisationPath());
	}

	EventQueue& Environment::GetEventQueue()
	{
		return event_queue;
	}

	void Environment::AddMesoscopicRegion(const Vec3d& origin, double length, const Vec3i& n_subvolumes, const std::vector<double>& diffusion_coefficients, int priority)
	{
		std::vector<Vec3i> removedSubvolumes;
		mesoscopic_regions.emplace_back(origin, length, n_subvolumes, diffusion_coefficients, removedSubvolumes, 
			priority, static_cast<int>(mesoscopic_regions.size()));
	}

	// the only type of relationship which does not need to be defined is a neighbour and none
	// if region a has a reflective surface and b is the neighbour
	void Environment::DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
		RelationshipPriority priority, SurfaceType ab_surface, SurfaceType ba_surface)
	{
		switch (priority)
		{
		case RelationshipPriority::A:
			GetMicroscopicRegion(region_a).AddLowPriorityRelative(GetMicroscopicRegion(region_b), ab_surface, GetMoleculeIDs());
			GetMicroscopicRegion(region_b).AddHighPriorityRelative(GetMicroscopicRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		case RelationshipPriority::B:
			GetMicroscopicRegion(region_a).AddHighPriorityRelative(GetMicroscopicRegion(region_b), ab_surface, GetMoleculeIDs());
			GetMicroscopicRegion(region_b).AddLowPriorityRelative(GetMicroscopicRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		case RelationshipPriority::None:
			GetMicroscopicRegion(region_a).AddNeighbour(GetMicroscopicRegion(region_b), ab_surface, GetMoleculeIDs());
			GetMicroscopicRegion(region_b).AddNeighbour(GetMicroscopicRegion(region_a), ba_surface, GetMoleculeIDs());
			break;
		default:
			LOG_CRITICAL("Unknown RelationshipPriority type");
			throw std::exception();
		}

		if (ab_surface == SurfaceType::None && ba_surface == SurfaceType::None)
		{
			GetMicroscopicRegion(region_a).LinkGrids(GetMicroscopicRegion(region_b), GetMoleculeIDs());
			GetMicroscopicRegion(region_a).LinkGrids(GetMicroscopicRegion(region_b), GetMoleculeIDs());
		}
	}

	void Environment::DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
		RelationshipPriority priority, microscopic::SurfaceType surface)
	{
		DefineRelationship(region_a, region_b, priority, surface, surface);
	}

	void Environment::DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
		RelationshipPriority priority,
		SurfaceTypes ab_surfaces, SurfaceTypes ba_surfaces)
	{
		int i = 0;
		switch (priority)
		{
		case RelationshipPriority::A:
			for (auto& ab_surface : ab_surfaces)
			{
				GetMicroscopicRegion(region_a).AddLowPriorityRelative(GetMicroscopicRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetMicroscopicRegion(region_b).AddHighPriorityRelative(GetMicroscopicRegion(region_a), ba_surface, { i });
				i++;
			}
			break;
		case RelationshipPriority::B:
			for (auto& ab_surface : ab_surfaces)
			{
				GetMicroscopicRegion(region_a).AddHighPriorityRelative(GetMicroscopicRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetMicroscopicRegion(region_b).AddLowPriorityRelative(GetMicroscopicRegion(region_a), ba_surface, { i });
				i++;
			}
			break;
		case RelationshipPriority::None:
			for (auto& ab_surface : ab_surfaces)
			{
				GetMicroscopicRegion(region_a).AddNeighbour(GetMicroscopicRegion(region_b), ab_surface, { i });
				i++;
			}
			i = 0;
			for (auto& ba_surface : ba_surfaces)
			{
				GetMicroscopicRegion(region_b).AddNeighbour(GetMicroscopicRegion(region_a), ba_surface, { i });
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
				GetMicroscopicRegion(region_a).LinkGrids(GetMicroscopicRegion(region_b), {i});
				GetMicroscopicRegion(region_a).LinkGrids(GetMicroscopicRegion(region_b), {i});
			}
		}
	}

	void Environment::DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
		RelationshipPriority priority, SurfaceTypes surfaces)
	{
		DefineRelationship(region_a, region_b, priority, surfaces, surfaces);
	}

	std::vector<std::unique_ptr<microscopic::Region>> Environment::microscopic_regions;
	std::vector<mesoscopic::Region> Environment::mesoscopic_regions;
	std::vector<std::unique_ptr<PassiveActor>> Environment::passive_actors;
	std::vector<std::unique_ptr<ActiveActor>> Environment::active_actors;
	double Environment::run_time = 0;
	double Environment::time = 0;
	int Environment::num_molecule_types = 0;
	std::string Environment::simulation_path = "simulation";
	int Environment::num_realisations = 1;
	int Environment::current_realisation = 0;
	uint64_t Environment::seed = 1;
	EventQueue Environment::event_queue;
}