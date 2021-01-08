#pragma once
#include "microscopic_region2.h"
#include "passive_actor.h"
#include "active_actor2.h"

namespace accord
{
	class Environment
	{
	public:
		static void Init(std::string simulation_name, int num_realisations,
			double run_time, int num_molecule_types, int num_microscopic_regions,
			int num_passive_actors, int num_active_actors, uint64_t seed, EventQueue5* event_queue);

		static void SetTime(double time);

		static double GetTime();

		static double GetRunTime();

		static int GetNumberOfMoleculeTypes();

		static std::string GetSimulationName();

		static int GetRealisationNumber();

		static microscopic::Region& GetRegion(RegionID id);

		static std::vector<microscopic::Region*> GetRegions(RegionIDs ids);

		static std::vector<std::unique_ptr<microscopic::Region>>& GetRegions();

		static std::vector<std::unique_ptr<PassiveActor>>& GetPassiveActors();

		static std::vector<std::unique_ptr<ActiveActor2>>& GetActiveActors();

		static std::string GetFilePath();

		static bool NextRealisation();

		static void CreateDirectories();

		static EventQueue5& GetEventQueue();

		enum class RelationshipPriority
		{
			A, B, None
		};

		static MoleculeIDs GetMoleculeIDs();

		static void LinkReactionsToRegions();

		typedef microscopic::SurfaceType SurfaceType;
		static void AddRegion(shape::basic::Box box, SurfaceType surface_type, 
			std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes, 
			double start_time, double time_step, int priority);

		static void AddRegion(shape::basic::Sphere sphere, SurfaceType surface_type,
			std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority);

		static void AddRegion(shape::basic::Cylinder cylinder, SurfaceType surface_type,
			std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority);
		
		static void DefineRelationship(RegionID region_a, RegionID region_b,
			RelationshipPriority priority,
			microscopic::SurfaceType ab_surface, microscopic::SurfaceType ba_surface);

		static void DefineRelationship(RegionID region_a, RegionID region_b,
			RelationshipPriority priority, microscopic::SurfaceType surface);

		typedef std::vector<microscopic::SurfaceType> SurfaceTypes;
		static void DefineRelationship(RegionID region_a, RegionID region_b,
			RelationshipPriority priority,
			SurfaceTypes ab_surfaces, SurfaceTypes ba_surfaces);

		static void DefineRelationship(RegionID region_a, RegionID region_b,
			RelationshipPriority priority, SurfaceTypes surfaces);
	private:
		static double time;
		static double run_time;
		static int num_molecule_types;
		static std::string simulation_name;
		static int num_realisations;
		static int current_realisation;
		static uint64_t seed;
		static EventQueue5* event_queue;

		static std::vector<std::unique_ptr<microscopic::Region>> microscopic_regions;
		static std::vector<std::unique_ptr<ActiveActor2>> active_actors;

		static std::vector<std::unique_ptr<PassiveActor>> passive_actors;
	};
}