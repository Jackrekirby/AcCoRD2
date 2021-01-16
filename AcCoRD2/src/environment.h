#pragma once
#include "microscopic_region.h"
#include "mesoscopic_region.h"
#include "passive_actor.h"
#include "active_actor.h"

namespace accord
{
	// need to rename all region functions to get microscopic region
	class Environment
	{
	public:
		static void Init(std::string simulation_path, int num_realisations,
			double run_time, int num_molecule_types, int num_microscopic_regions,
			int num_mesoscopic_regions, int num_passive_actors, int num_active_actors, 
			uint64_t seed);

		static void SetTime(double time);

		static double GetTime();

		static double GetRunTime();

		static int GetNumberOfMoleculeTypes();

		static std::string GetSimulationPath();

		static int GetRealisationNumber();


		static microscopic::Region& GetMicroscopicRegion(const MicroscopicRegionID& id);

		static std::vector<microscopic::Region*> GetRegions(const MicroscopicRegionIDs& ids);

		static std::vector<std::unique_ptr<microscopic::Region>>& GetRegions();


		static mesoscopic::Region& GetMesoscopicRegion(const MesoscopicRegionID& id);

		static std::vector<mesoscopic::Region*> GetMesoscopicRegions(const MesoscopicRegionIDs& ids);

		static std::vector<mesoscopic::Region>& GetMesoscopicRegions();

		static std::vector<std::unique_ptr<PassiveActor>>& GetPassiveActors();

		static std::vector<std::unique_ptr<ActiveActor>>& GetActiveActors();


		static std::string GetRealisationPath();

		static bool NextRealisation();

		static void CreateDirectories();

		static EventQueue& GetEventQueue();

		enum class RelationshipPriority
		{
			A, B, None
		};

		static MoleculeIDs GetMoleculeIDs();

		static void LinkReactionsToRegions();

		typedef microscopic::SurfaceType SurfaceType;
		static void AddRegion(shape::basic::Box box, SurfaceType surface_type, 
			const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes, 
			double time_step, int priority);

		static void AddRegion(shape::basic::Sphere sphere, SurfaceType surface_type,
			const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
			double time_step, int priority);

		static void AddRegion(shape::basic::Cylinder cylinder, SurfaceType surface_type,
			const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
			double time_step, int priority);
		
		static void DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
			RelationshipPriority priority,
			microscopic::SurfaceType ab_surface, microscopic::SurfaceType ba_surface);

		static void DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
			RelationshipPriority priority, microscopic::SurfaceType surface);

		typedef std::vector<microscopic::SurfaceType> SurfaceTypes;
		static void DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
			RelationshipPriority priority,
			SurfaceTypes ab_surfaces, SurfaceTypes ba_surfaces);

		static void DefineRelationship(const MicroscopicRegionID& region_a, const MicroscopicRegionID& region_b,
			RelationshipPriority priority, SurfaceTypes surfaces);
	private:
		static double time;
		static double run_time;
		static int num_molecule_types;
		static std::string simulation_path;
		static int num_realisations;
		static int current_realisation;
		static uint64_t seed;
		static EventQueue event_queue;

		static std::vector<std::unique_ptr<microscopic::Region>> microscopic_regions;
		static std::vector<mesoscopic::Region> mesoscopic_regions;
		static std::vector<std::unique_ptr<ActiveActor>> active_actors;
		static std::vector<std::unique_ptr<PassiveActor>> passive_actors;
	};
}