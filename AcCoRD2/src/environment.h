#pragma once
#include "microscopic_region2.h"
#include "passive_actor.h"

namespace accord
{
	class Environment
	{
	public:
		static void Init(std::string simulation_name, int num_realisations,
			double run_time, int num_molecule_types, int num_microscopic_regions,
			uint64_t seed);

		static void SetTime(double time);

		static double GetTime();

		static double GetRunTime();

		static int GetNumberOfMoleculeTypes();

		static std::string GetSimulationName();

		static int GetRealisationNumber();

		static microscopic::Region2& GetRegion(RegionID id);

		static std::vector<std::unique_ptr<microscopic::Region2>>& GetRegions();

		static std::vector<std::unique_ptr<PassiveActor>>& GetPassiveActors();

		static std::string GetFilePath();

		static bool NextRealisation();

		static void CreateDirectories();
	private:
		static double time;
		static double run_time;
		static int num_molecule_types;
		static std::string simulation_name;
		static int num_realisations;
		static int current_realisation;
		static uint64_t seed;

		static std::vector<std::unique_ptr<microscopic::Region2>> microscopic_regions;

		static std::vector<std::unique_ptr<PassiveActor>> passive_actors;
	};
}