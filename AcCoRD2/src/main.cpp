#include "pch.h"
#include "event_queue_test.h"
#include "microscopic_region.h"
#include "environment.h"
#include "event_queue.h"
#include "event.h"
#include "passive_actor.h"
#include "shapeless_passive_actor.h"
#include "box_passive_actor.h"
#include "microscopic_box_surface_shape.h"
#include "microscopic_surface_shape.h"
#include "microscopic_sphere_surface_shape.h"
#include "microscopic_cylinder_surface_shape.h"
#include "collision_cylinder.h"
#include "relation_cylinder.h"
#include "relation_sphere.h"

#include "microscopic_box_region.h"
#include "microscopic_cylinder_region.h"
#include "microscopic_sphere_region.h"
#include "reaction_manager.h"
//#include "passive_actor2.h"

#include "active_actor_shape.h"
#include "active_actor_random_time.h"
#include "active_actor_non_random.h"
#include "active_actor_random_bits.h"

#include "mesoscopic_region.h"
#include "config_importer.h"

void TestSimpleEnvironment2()
{
	using namespace accord;

	// SIMULATION ============================================================================================================
	std::string sim_dir = "D:/dev/my_simulation5";
	Environment::Init(sim_dir, 1, 1, 4, 1, 0, 1, 0, 1);
	//Random::GetGenerator().advance(2);

	// CREATE REGIONS ========================================================================================================
	std::vector<double> diffision_coefficients = { 0.1, 0.1, 0.1, 0.1 };
	std::vector<Vec3i> n_subvolumes = { Vec3i(1), Vec3i(1), Vec3i(1), Vec3i(1) };
	double start_time = 0, time_step = 0.05;
	int priority = 0;

	shape::basic::Box box1(Vec3d(-1), Vec3d(2));

	Environment::AddRegion(box1, microscopic::SurfaceType::Reflecting,
		diffision_coefficients, n_subvolumes, time_step, priority);

	// CREATE ACTIVE ACTORS =======================
	//double action_interval = Environment::GetRunTime() / 10;
	//double release_interval = action_interval / 2;
	//int modulation_strength = 10;
	//MoleculeIDs release_molecules = { 1 };
	//ActiveActorRandomTime active_actor(action_interval, release_interval, release_molecules, 
	//	modulation_strength, Environment::GetRegions({ 0 }), std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)), 
	//	start_time, 0, &event_queue, 0);

	// add check environment run time / action interval == length bits / n_modulation_bits (unless max events set)
	//double action_interval = Environment::GetRunTime() / 5;
	//double release_interval = action_interval / 2;
	//double slot_interval = release_interval / 1;
	//int modulation_strength = 1;
	//int n_modulation_bits = 2;
	//MoleculeIDs release_molecules = { 1 };
	//ActiveActorNonRandom active_actor(action_interval, release_interval, slot_interval, 
	//	{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 1}, n_modulation_bits, Environment::GetRealisationPath() + "a1_b.bin", release_molecules,
	//	modulation_strength, Environment::GetRegions({ 0 }), std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)),
	//	start_time, 5, &event_queue, 0);

	double action_interval = Environment::GetRunTime() / 5;
	double release_interval = action_interval / 2;
	double slot_interval = release_interval / 1;
	int modulation_strength = 1;
	int n_modulation_bits = 1;
	double bit_probability = 0.5;
	MoleculeIDs release_molecules = { 1, 2 };
	Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomBits>(
		action_interval, release_interval, slot_interval,
		bit_probability, n_modulation_bits,
		release_molecules, modulation_strength, Environment::GetRegions({ 0 }), Environment::GetMesoscopicRegions({}),
		std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)), start_time, 5, 0));

	Json json_regions;
	for (auto& regions : Environment::GetRegions())
	{
		json_regions["shapes"].emplace_back(regions->GetShape().GetBasicShape());
	}
	std::ofstream region_file(sim_dir + "/regions.json");
	region_file << JsonToString(json_regions);
	region_file.close();

	// CREATE ACTORS =============================================================================================================
	Environment::GetPassiveActors().reserve(Environment::GetRegions().size());
	for (int i = 0; i < Environment::GetRegions().size(); i++)
	{
		//Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({ i }),
		//	MesoscopicRegionIDs({ }), MoleculeIDs({ 0, 1, 2, 3 }), 0, -1, time_step, i, true, true));
	}

	Json json_actors, shapeless_actor;
	shapeless_actor["type"] = "none";
	for (auto& passive_actor : Environment::GetPassiveActors())
	{
		if (passive_actor->GetShape() == nullptr)
		{
			json_actors["shapes"].emplace_back(shapeless_actor);
		}
		else
		{
			json_actors["shapes"].emplace_back(*(passive_actor->GetShape()));
		}
	}
	std::ofstream actors_file(sim_dir + "/actors.json");
	actors_file << JsonToString(json_actors);
	actors_file.close();

	// Add Events to Event Queue
	for (auto& region : Environment::GetRegions())
	{
		Environment::GetEventQueue().Add(region.get());
	}

	for (auto& actor : Environment::GetPassiveActors())
	{
		Environment::GetEventQueue().Add(actor.get());
	}

	for (auto& actor : Environment::GetActiveActors())
	{
		Environment::GetEventQueue().Add(actor.get());
	}

	// BEGIN SIMULATION LOOP ======================================================================================================
	do {
		if (Environment::GetRealisationNumber() > 0)
		{
			for (auto& passive_actor : Environment::GetPassiveActors())
			{
				passive_actor->NextRealisation();
			}
			for (auto& region : Environment::GetRegions())
			{
				region->NextRealisation();
			}
		}
		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
		while (true)
		{
			auto& event = Environment::GetEventQueue().Front();
			Environment::SetTime(event.GetEventTime());
			if (Environment::GetTime() > Environment::GetRunTime())
			{
				//LOG_INFO("The Next Event Outside Run Time : ({})", event);
				break;
			}
			//LOG_INFO("Time = {}, EventID = {}, EventType = {}", Environment::GetTime(), event.GetID(), event.GetType());
			//LOG_INFO("Event:({})", event);
			event.Run();
		}
	} while (Environment::NextRealisation());

	LOG_INFO("Cleaning Up");
}





void TestMesoscopic()
{
	using namespace accord;
	int n_micro_regions = 0, n_meso_regions = 2, n_passive_actors = n_meso_regions + n_micro_regions, n_active_actors = 1, n_molecule_types = 3;
	Environment::Init("D:/dev/meso_sim", 1, 10, n_molecule_types, n_micro_regions, n_meso_regions, n_passive_actors, n_active_actors, 1);
	LOG_INFO("simulation path = {}", Environment::GetSimulationPath());

	Vec3i start_subvolume(1, 1, 1);
	Vec3i end_subvolume(2, 2, 2);
	std::vector<Vec3i> remove_subvolumes;
	Vec3i i;
	for (i.z = start_subvolume.z; i.z <= end_subvolume.z; i.z++)
	{
		for (i.y = start_subvolume.y; i.y <= end_subvolume.y; i.y++)
		{
			for (i.x = start_subvolume.x; i.x <= end_subvolume.x; i.x++)
			{
				LOG_INFO("remove = {}", i);
				remove_subvolumes.emplace_back(i);
			}
		}
	}


	Environment::GetMesoscopicRegions().emplace_back(Vec3d(0), 1, Vec3i(3, 3, 3), std::vector<double>{1, 1, 1}, remove_subvolumes, 0, 0);
	Environment::GetMesoscopicRegions().emplace_back(Vec3d(3, 0, 0), 1, Vec3i(3, 3, 3), std::vector<double>{1, 1, 1}, std::vector<Vec3i>{}, 0, 1);

	
	Environment::GetMesoscopicRegion(1).AddNeighbour(Environment::GetMesoscopicRegion(0));
	Environment::GetMesoscopicRegion(0).AddNeighbour(Environment::GetMesoscopicRegion(1));
	

	//Environment::GetMesoscopicRegions().at(0).AddZerothOrderReaction({ 0 }, 1);
	//Environment::GetMesoscopicRegions().at(0).AddFirstOrderReaction(1, {2}, 1);
	//Environment::GetMesoscopicRegions().at(0).AddSecondOrderReaction(0, 1, { 2 }, 1);

	//ReactionManager::AddSecondOrderReaction(0, 1, { 2 }, 0, 0, 1, {}, { 0 });
	//Environment::LinkReactionsToRegions();

	//Environment::GetMesoscopicRegion(0).RemoveInterior(Vec3d(2, 2, 0), Vec3d(1, 1, 3));
	for (auto& meso_region : Environment::GetMesoscopicRegions())
	{
		Environment::GetEventQueue().Add(&meso_region);
		meso_region.LinkSiblingSubvolumes();
		meso_region.AddSubvolumesToQueue();
	}

	double action_interval = Environment::GetRunTime() / 5;
	double release_interval = action_interval / 2;
	double slot_interval = release_interval / 5;
	int modulation_strength = 1;
	int n_modulation_bits = 2;
	double bit_probability = 0.3;
	MoleculeIDs release_molecules = { 0, 1, 2 };
	//
	Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomBits>(
		action_interval, release_interval, slot_interval,
		bit_probability, n_modulation_bits,
		release_molecules, modulation_strength, Environment::GetRegions({}), Environment::GetMesoscopicRegions({0}),
		std::make_unique<ActiveActorBox>(Vec3d(0), Vec3d(1, 1, 1)), 0, 5, 0));

	for (int i = 0; i < 0; i++)
	{
		//Environment::GetMesoscopicRegion(0).AddMolecule(i % 2, { 0.5, 0.5, 0.5 });
		Environment::GetMesoscopicRegion(0).AddMolecule(0, { 3.5, 0.5, 0.5 });
	}
	
	//ShapelessPassiveActor(const MicroscopicRegionIDs& microscopic_region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time);

	double time_step = 0.05;
	Environment::GetPassiveActors().reserve(Environment::GetMesoscopicRegions().size());
	LOG_INFO(Environment::GetMesoscopicRegions().size());
	for (int i = 0; i < Environment::GetMesoscopicRegions().size(); i++)
	{
		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({ }),
			MesoscopicRegionIDs({ MesoscopicRegionID(i) }), MoleculeIDs({ 0, 1, 2 }), 0, -1, time_step, PassiveActorID(i), true, true));
	}

	Json json_regions;
	for (auto& region : Environment::GetMesoscopicRegions())
	{
		Json mesoscopic_region;
		mesoscopic_region["box"] = static_cast<shape::basic::Box>(region.GetBoundingBox());
		for (auto& subvolume : region.GetSubvolumes())
		{
			mesoscopic_region["subvolumes"].emplace_back(static_cast<shape::basic::Box>(subvolume.GetBoundingBox()));
		}
		json_regions["mesoscopic"].emplace_back(mesoscopic_region);
	}
	//std::ofstream subvolume_file(Environment::GetSimulationPath() + "/subvolumes.json");
	//subvolume_file << JsonToString(json_subvolumes); subvolume_file.close();
	std::ofstream region_file(Environment::GetSimulationPath() + "/regions.json");
	region_file << JsonToString(json_regions); region_file.close();

	Json json_actors, shapeless_actor;
	shapeless_actor["type"] = "none";
	for (auto& passive_actor : Environment::GetPassiveActors())
	{
		if (passive_actor->GetShape() == nullptr)
		{
			json_actors["shapes"].emplace_back(shapeless_actor);
		}
		else
		{
			json_actors["shapes"].emplace_back(*(passive_actor->GetShape()));
		}
	}
	std::ofstream actors_file(Environment::GetSimulationPath() + "/passive_actors.json");
	actors_file << JsonToString(json_actors);
	actors_file.close();


	json_actors.clear();
	for (auto& actor : Environment::GetActiveActors())
	{
		json_actors["shapes"].emplace_back(actor->GetShape());
	}
	std::ofstream active_actors_file(Environment::GetSimulationPath() + "/active_actors.json");
	active_actors_file << JsonToString(json_actors);
	active_actors_file.close();

	for (auto& actor : Environment::GetPassiveActors())
	{
		Environment::GetEventQueue().Add(actor.get());
	}

	for (auto& actor : Environment::GetActiveActors())
	{
		Environment::GetEventQueue().Add(actor.get());
	}

	//LOG_INFO("next event = {}", event_queue.Front());
	//LOG_INFO("region event time = {}, ", region.GetEventTime());

	//LOG_INFO(event_queue.Front());

	do {
		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
		if (Environment::GetRealisationNumber() > 0)
		{
			for (auto& passive_actor : Environment::GetPassiveActors())
			{
				passive_actor->NextRealisation();
			}
			for (auto& region : Environment::GetRegions())
			{
				region->NextRealisation();
			}
			for (auto& active_actors : Environment::GetActiveActors())
			{
				active_actors->NextRealisation();
			}
			for (auto& region : Environment::GetMesoscopicRegions())
			{
				region.NextRealisation();
			}
		}
		while (true)
		{
			//Environment::GetMesoscopicRegion(0).Print();
			//Environment::GetMesoscopicRegion(1).Print();
			auto& event = Environment::GetEventQueue().Front();
			Environment::SetTime(event.GetEventTime());
			if (Environment::GetTime() > Environment::GetRunTime())
			{
				break;
			}
			//LOG_INFO("Event:({})", event.LogEvent());
			event.Run();
		}
	} while (Environment::NextRealisation());
}

//   ensure naming consistency with id's and ptrs. avoid id name unless local to function only
// X to avoid passive id to each object just store static variable?
// * remove start time from regions
//   ensure consistency with passing ids and passing objects. Only pass ids if then not just calling environment in constructor
//   pass shapes by const ref
//   pass enums by const ref
// X does FirstOrderReaction and SecondOrderReaction for microscopic regions need a next realisation function?
// 	 test delete area of mesoscopic region
// check logging of array of array of ints
// region relationship of type none should be done automatically for neighbours (would require region relation checking)
// finish adding in range functions for arrays
// RenameIsInt to ThrowIfNotInt

// current relationships are only for microscopci regions
// need to be able to search in microscopic regions only

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");       
	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	accord::CreateEnvironment();
}