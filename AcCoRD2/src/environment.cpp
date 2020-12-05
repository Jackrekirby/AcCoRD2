#include "pch.h"
#include "environment.h"


namespace accord
{
	void Environment::Init(std::string simulation_name, int num_realisations, 
		double run_time, int num_molecule_types, int num_microscopic_regions,
		uint64_t seed = 1)
	{
		Environment::time = 0;
		Environment::run_time = run_time;
		Environment::num_molecule_types = num_molecule_types;
		Environment::microscopic_regions.reserve(num_microscopic_regions);
		Environment::simulation_name = simulation_name;
		Environment::num_realisations = num_realisations;
		Environment::current_realisation = 0;

		Random::SetSeed(seed);
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

	std::string Environment::GetSimulationName()
	{
		return simulation_name;
	}

	int Environment::GetRealisationNumber()
	{
		return current_realisation;
	}

	std::string Environment::GetFilePath()
	{
		return Environment::GetSimulationName() +
			"/s" + std::to_string(Environment::seed) +
			"/r" + std::to_string(Environment::current_realisation) +
			"/";
	}

	std::vector<microscopic::Region2> Environment::microscopic_regions;
	double Environment::run_time = 0;
	double Environment::time = 0;
	int Environment::num_molecule_types = 0;
	std::string Environment::simulation_name = "simulation";
	int Environment::num_realisations = 1;
	int Environment::current_realisation = 0;
	int Environment::seed = 1;
}