#pragma once
#include "microscopic_region2.h"

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

		static std::vector<microscopic::Region2> microscopic_regions;

		static std::string GetFilePath();
	private:
		static double time;
		static double run_time;
		static int num_molecule_types;
		static std::string simulation_name;
		static int num_realisations;
		static int current_realisation;
		static int seed;
	};
}