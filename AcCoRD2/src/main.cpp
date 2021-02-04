#include "pch.h"
#include "environment.h"
#include "config_importer.h"

//void TestSimpleEnvironment2()
//{
//	using namespace accord;
//
//	// SIMULATION ============================================================================================================
//	std::string sim_dir = "D:/dev/my_simulation5";
//	Environment::Init(sim_dir, 1, 1, 4, 1, 0, 1, 0, 1);
//	//Random::GetGenerator().advance(2);
//
//	// CREATE REGIONS ========================================================================================================
//	std::vector<double> diffision_coefficients = { 0.1, 0.1, 0.1, 0.1 };
//	std::vector<Vec3i> n_subvolumes = { Vec3i(1), Vec3i(1), Vec3i(1), Vec3i(1) };
//	double start_time = 0, time_step = 0.05;
//	int priority = 0;
//
//	shape::basic::Box box1(Vec3d(-1), Vec3d(2));
//
//	Environment::AddRegion(box1, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, time_step, priority);
//
//	// CREATE ACTIVE ACTORS =======================
//	//double action_interval = Environment::GetRunTime() / 10;
//	//double release_interval = action_interval / 2;
//	//int modulation_strength = 10;
//	//MoleculeIDs release_molecules = { 1 };
//	//ActiveActorRandomTime active_actor(action_interval, release_interval, release_molecules, 
//	//	modulation_strength, Environment::GetRegions({ 0 }), std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)), 
//	//	start_time, 0, &event_queue, 0);
//
//	// add check environment run time / action interval == length bits / n_modulation_bits (unless max events set)
//	//double action_interval = Environment::GetRunTime() / 5;
//	//double release_interval = action_interval / 2;
//	//double slot_interval = release_interval / 1;
//	//int modulation_strength = 1;
//	//int n_modulation_bits = 2;
//	//MoleculeIDs release_molecules = { 1 };
//	//ActiveActorNonRandom active_actor(action_interval, release_interval, slot_interval, 
//	//	{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 1}, n_modulation_bits, Environment::GetRealisationPath() + "a1_b.bin", release_molecules,
//	//	modulation_strength, Environment::GetRegions({ 0 }), std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)),
//	//	start_time, 5, &event_queue, 0);
//
//	double action_interval = Environment::GetRunTime() / 5;
//	double release_interval = action_interval / 2;
//	double slot_interval = release_interval / 1;
//	int modulation_strength = 1;
//	int n_modulation_bits = 1;
//	double bit_probability = 0.5;
//	std::vector<int> release_molecules = { 1, 1, 0, 0 };
//	Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomBits>(
//		action_interval, release_interval, slot_interval,
//		bit_probability, n_modulation_bits,
//		release_molecules, modulation_strength, Environment::GetRegions({ 0 }), Environment::GetMesoscopicRegions({}),
//		std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)), start_time, 5, 0));
//
//	Json json_regions;
//	for (auto& regions : Environment::GetRegions())
//	{
//		json_regions["shapes"].emplace_back(regions->GetShape().GetBasicShape());
//	}
//	std::ofstream region_file(sim_dir + "/regions.json");
//	region_file << JsonToString(json_regions);
//	region_file.close();
//
//	// CREATE ACTORS =============================================================================================================
//	Environment::GetPassiveActors().reserve(Environment::GetRegions().size());
//	for (int i = 0; i < Environment::GetRegions().size(); i++)
//	{
//		//Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({ i }),
//		//	MesoscopicRegionIDs({ }), MoleculeIDs({ 0, 1, 2, 3 }), 0, -1, time_step, i, true, true));
//	}
//
//	Json json_actors, shapeless_actor;
//	shapeless_actor["type"] = "none";
//	for (auto& passive_actor : Environment::GetPassiveActors())
//	{
//		if (passive_actor->GetShape() == nullptr)
//		{
//			json_actors["shapes"].emplace_back(shapeless_actor);
//		}
//		else
//		{
//			json_actors["shapes"].emplace_back(*(passive_actor->GetShape()));
//		}
//	}
//	std::ofstream actors_file(sim_dir + "/actors.json");
//	actors_file << JsonToString(json_actors);
//	actors_file.close();
//
//	// Add Events to Event Queue
//	for (auto& region : Environment::GetRegions())
//	{
//		Environment::GetEventQueue().Add(region.get());
//	}
//
//	for (auto& actor : Environment::GetPassiveActors())
//	{
//		Environment::GetEventQueue().Add(actor.get());
//	}
//
//	for (auto& actor : Environment::GetActiveActors())
//	{
//		Environment::GetEventQueue().Add(actor.get());
//	}
//
//	// BEGIN SIMULATION LOOP ======================================================================================================
//	do {
//		if (Environment::GetRealisationNumber() > 0)
//		{
//			for (auto& passive_actor : Environment::GetPassiveActors())
//			{
//				passive_actor->NextRealisation();
//			}
//			for (auto& region : Environment::GetRegions())
//			{
//				region->NextRealisation();
//			}
//		}
//		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
//		while (true)
//		{
//			auto& event = Environment::GetEventQueue().Front();
//			Environment::SetTime(event.GetEventTime());
//			if (Environment::GetTime() > Environment::GetRunTime())
//			{
//				//LOG_INFO("The Next Event Outside Run Time : ({})", event);
//				break;
//			}
//			//LOG_INFO("Time = {}, EventID = {}, EventType = {}", Environment::GetTime(), event.GetID(), event.GetType());
//			//LOG_INFO("Event:({})", event);
//			event.Run();
//		}
//	} while (Environment::NextRealisation());
//
//	LOG_INFO("Cleaning Up");
//}
//
//void TestMesoscopic()
//{
//	using namespace accord;
//	int n_micro_regions = 0, n_meso_regions = 2, n_passive_actors = n_meso_regions + n_micro_regions, n_active_actors = 1, n_molecule_types = 3;
//	Environment::Init("D:/dev/meso_sim", 1, 10, n_molecule_types, n_micro_regions, n_meso_regions, n_passive_actors, n_active_actors, 1);
//	LOG_INFO("simulation path = {}", Environment::GetSimulationPath());
//
//	Vec3i start_subvolume(1, 1, 1);
//	Vec3i end_subvolume(2, 2, 2);
//	std::vector<Vec3i> remove_subvolumes;
//	Vec3i i;
//	for (i.z = start_subvolume.z; i.z <= end_subvolume.z; i.z++)
//	{
//		for (i.y = start_subvolume.y; i.y <= end_subvolume.y; i.y++)
//		{
//			for (i.x = start_subvolume.x; i.x <= end_subvolume.x; i.x++)
//			{
//				LOG_INFO("remove = {}", i);
//				remove_subvolumes.emplace_back(i);
//			}
//		}
//	}
//
//	Environment::GetMesoscopicRegions().emplace_back(Vec3d(0), 1, Vec3i(3, 3, 3), std::vector<double>{1, 1, 1}, remove_subvolumes, 0, 0);
//	Environment::GetMesoscopicRegions().emplace_back(Vec3d(3, 0, 0), 1, Vec3i(3, 3, 3), std::vector<double>{1, 1, 1}, std::vector<Vec3i>{}, 0, 1);
//
//	Environment::GetMesoscopicRegion(1).AddNeighbour(Environment::GetMesoscopicRegion(0));
//	Environment::GetMesoscopicRegion(0).AddNeighbour(Environment::GetMesoscopicRegion(1));
//	
//
//	//Environment::GetMesoscopicRegions().at(0).AddZerothOrderReaction({ 0 }, 1);
//	//Environment::GetMesoscopicRegions().at(0).AddFirstOrderReaction(1, {2}, 1);
//	//Environment::GetMesoscopicRegions().at(0).AddSecondOrderReaction(0, 1, { 2 }, 1);
//
//	//ReactionManager::AddSecondOrderReaction(0, 1, { 2 }, 0, 0, 1, {}, { 0 });
//	//Environment::LinkReactionsToRegions();
//
//	//Environment::GetMesoscopicRegion(0).RemoveInterior(Vec3d(2, 2, 0), Vec3d(1, 1, 3));
//	for (auto& meso_region : Environment::GetMesoscopicRegions())
//	{
//		Environment::GetEventQueue().Add(&meso_region);
//		meso_region.LinkSiblingSubvolumes();
//		meso_region.AddSubvolumesToQueue();
//	}
//
//	double action_interval = Environment::GetRunTime() / 5;
//	double release_interval = action_interval / 2;
//	double slot_interval = release_interval / 5;
//	int modulation_strength = 1;
//	int n_modulation_bits = 2;
//	double bit_probability = 0.3;
//	std::vector<int> release_molecules = { 0, 1, 1 };
//	//
//	Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomBits>(
//		action_interval, release_interval, slot_interval,
//		bit_probability, n_modulation_bits,
//		release_molecules, modulation_strength, Environment::GetRegions({}), Environment::GetMesoscopicRegions({0}),
//		std::make_unique<ActiveActorBox>(Vec3d(0), Vec3d(1, 1, 1)), 0, 5, 0));
//
//	for (int i = 0; i < 0; i++)
//	{
//		//Environment::GetMesoscopicRegion(0).AddMolecule(i % 2, { 0.5, 0.5, 0.5 });
//		Environment::GetMesoscopicRegion(0).AddMolecule(0, { 3.5, 0.5, 0.5 });
//	}
//	
//	//ShapelessPassiveActor(const MicroscopicRegionIDs& microscopic_region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time);
//
//	double time_step = 0.05;
//	Environment::GetPassiveActors().reserve(Environment::GetMesoscopicRegions().size());
//	LOG_INFO(Environment::GetMesoscopicRegions().size());
//	for (int i = 0; i < Environment::GetMesoscopicRegions().size(); i++)
//	{
//		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({ }),
//			MesoscopicRegionIDs({ MesoscopicRegionID(i) }), MoleculeIDs({ 0, 1, 2 }), 0, -1, time_step, PassiveActorID(i), true, true));
//	}
//
//	Json json_regions;
//	for (auto& region : Environment::GetMesoscopicRegions())
//	{
//		Json mesoscopic_region;
//		mesoscopic_region["box"] = static_cast<shape::basic::Box>(region.GetBoundingBox());
//		for (auto& subvolume : region.GetSubvolumes())
//		{
//			mesoscopic_region["subvolumes"].emplace_back(static_cast<shape::basic::Box>(subvolume.GetBoundingBox()));
//		}
//		json_regions["mesoscopic"].emplace_back(mesoscopic_region);
//	}
//	//std::ofstream subvolume_file(Environment::GetSimulationPath() + "/subvolumes.json");
//	//subvolume_file << JsonToString(json_subvolumes); subvolume_file.close();
//	std::ofstream region_file(Environment::GetSimulationPath() + "/regions.json");
//	region_file << JsonToString(json_regions); region_file.close();
//
//	Json json_actors, shapeless_actor;
//	shapeless_actor["type"] = "none";
//	for (auto& passive_actor : Environment::GetPassiveActors())
//	{
//		if (passive_actor->GetShape() == nullptr)
//		{
//			json_actors["shapes"].emplace_back(shapeless_actor);
//		}
//		else
//		{
//			json_actors["shapes"].emplace_back(*(passive_actor->GetShape()));
//		}
//	}
//	std::ofstream actors_file(Environment::GetSimulationPath() + "/passive_actors.json");
//	actors_file << JsonToString(json_actors);
//	actors_file.close();
//
//
//	json_actors.clear();
//	for (auto& actor : Environment::GetActiveActors())
//	{
//		json_actors["shapes"].emplace_back(actor->GetShape());
//	}
//	std::ofstream active_actors_file(Environment::GetSimulationPath() + "/active_actors.json");
//	active_actors_file << JsonToString(json_actors);
//	active_actors_file.close();
//
//	for (auto& actor : Environment::GetPassiveActors())
//	{
//		Environment::GetEventQueue().Add(actor.get());
//	}
//
//	for (auto& actor : Environment::GetActiveActors())
//	{
//		Environment::GetEventQueue().Add(actor.get());
//	}
//
//	//LOG_INFO("next event = {}", event_queue.Front());
//	//LOG_INFO("region event time = {}, ", region.GetEventTime());
//
//	//LOG_INFO(event_queue.Front());
//
//	do {
//		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
//		if (Environment::GetRealisationNumber() > 0)
//		{
//			for (auto& passive_actor : Environment::GetPassiveActors())
//			{
//				passive_actor->NextRealisation();
//			}
//			for (auto& region : Environment::GetRegions())
//			{
//				region->NextRealisation();
//			}
//			for (auto& active_actors : Environment::GetActiveActors())
//			{
//				active_actors->NextRealisation();
//			}
//			for (auto& region : Environment::GetMesoscopicRegions())
//			{
//				region.NextRealisation();
//			}
//		}
//		while (true)
//		{
//			//Environment::GetMesoscopicRegion(0).Print();
//			//Environment::GetMesoscopicRegion(1).Print();
//			auto& event = Environment::GetEventQueue().Front();
//			Environment::SetTime(event.GetEventTime());
//			if (Environment::GetTime() > Environment::GetRunTime())
//			{
//				break;
//			}
//			//LOG_INFO("Event:({})", event.LogEvent());
//			event.Run();
//		}
//	} while (Environment::NextRealisation());
//}

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
// turn microscopic surface type into surface type per molecule type
// consider grouping all optional json keys 
// mesoscopic region no logn need to link sibling subvolumes and subvoluem queues later as none are deleted
// import shapes from config file in MATLAB
// https://uk.mathworks.com/matlabcentral/answers/724917-forcing-a-scalar-to-be-represented-as-a-1x1-vector
// clean up matlab compilation
// still need visualisation of debug paths
// switch molecule format from vector of molecule IDs to vector of number of molecules per type
// reactions
// active actors
// is a propensity link to products required because products do not affect the propensity of reactions?
// add maximum number of reflections to json config file
// make colours of molecules and regions match
// change active actors to release products according to [5, 6, 2, 0, 1]
// update modulation stength from int to double
// what is burst mode?
// add remaining active actor constructors to config
// current molecule generation either by reactions or active actors can be in child regions
// rename molecule type to release to NumberOfMoleculeToReleasePerMoleculeType
// update molecule generation in mesoscopic regions
// may need to update is overlapping box code as it includes neighbouring.
// surfaces on the boundary of two rect regions will 'overlap' / 'be neighbours' of both surfaces, even if you want the surface to ownly release molecules onto one region
// only volume actors should be allowed to be specified by multiple regions
// need to catch cells in MATLAB

namespace accord
{
	class Timer
	{
	public:
		Timer()
		{
			start_time_point = std::chrono::high_resolution_clock::now();
		}

		double Stop()
		{
			auto end_time_point = std::chrono::high_resolution_clock::now();

			auto start_time = std::chrono::time_point_cast<std::chrono::milliseconds>(start_time_point).time_since_epoch();

			auto end_time = std::chrono::time_point_cast<std::chrono::milliseconds>(end_time_point).time_since_epoch();

			auto duration = end_time - start_time;
			return static_cast<double>(duration.count()) * 0.001;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
	};

	void Run(const std::string& config_filepath)
	{
		Timer timer1;
		ConfigImporter config(config_filepath);
		//LOG_INFO(accord::JsonToPrettyString(config.GetJson()));
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

// should low priority relative IsRegion be true for meso?
// add mesoscopic relationships for certain molecule types
// draw active actor points
// add uniform flow
// add passive actor per mesoscopic subvolume

// If subvolumes of another molecule type are a different size are they linking?
#include "collision_cylinder.h"
int main()
{
	accord::Run("C:/dev/AcCoRD2/configs/bimolecular_reactions1.json");
}