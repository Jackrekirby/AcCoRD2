#include "pch.h"
#include "environment.h"
#include "config_importer.h"
#include "timer.h"

namespace accord
{
	void Run(const std::string& config_filepath)
	{
		Timer timer1;
		ConfigImporter config(config_filepath);
		Environment::LinkReactionsToRegions();
		Environment::AddEventsToEventQueue();
		LOG_INFO("Build Time = {}s", timer1.Stop());
		Timer timer2;
		LOG_INFO("Starting Simulation");
		Environment::RunSimulation();
		LOG_INFO("Run Time = {}s", timer2.Stop());
		LOG_INFO("Cleaning Memory");
	}
}

int main()
{
	accord::Run("C:/dev/AcCoRD2/configs/narrow_box_tube.json");
}