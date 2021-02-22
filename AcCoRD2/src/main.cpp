#include "pch.h"
#include "environment.h"
#include "config_importer.h"
#include "timer.h"

namespace accord
{
	void Run(const std::string& config_filepath)
	{
		Timer timer;
		ConfigImporter config(config_filepath);
		Environment::LinkReactionsToRegions();
		Environment::AddEventsToEventQueue();
		LOG_INFO("Build Time: {:.3f}s", timer.GetTime());
		timer.Reset();
		LOG_INFO("Starting Simulation");
		Environment::RunSimulation();
		LOG_INFO("Run Time: {:.3f}s", timer.GetTime());
		LOG_INFO("Cleaning Memory");
	}
}

int main()
{
	accord::Run("C:/dev/AcCoRD2/configs/simple_micro.json");
}