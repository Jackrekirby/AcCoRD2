#include "pch.h"
#include "event_queue_test.h"
#include "microscopic_region2.h"
#include "environment.h"
#include "event_queue5.h"
#include "event5.h"
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
#include "basic_shape_3d.h"
#include "passive_actor2.h"

#include "active_actor_shape.h"
#include "active_actor_random_time.h"
#include "active_actor_non_random.h"
#include "active_actor_random_bits.h"

#include "mesoscopic_region.h"

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
		diffision_coefficients, n_subvolumes, start_time, time_step, priority);

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
		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroRegionIDs({ i }),
			MicroRegionIDs({ i }), MoleculeIDs({ 0, 1, 2, 3 }), 0, -1, time_step,
			static_cast<int>(Environment::GetPassiveActors().size()), true, true));
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
			LOG_INFO("Event:({})", event);
			event.Run();
		}
	} while (Environment::NextRealisation());

	LOG_INFO("Cleaning Up");
}

//void TestSimpleEnvironment()
//{
//	using namespace accord;
//
//	// SIMULATION ============================================================================================================
//	std::string sim_dir = "D:/dev/my_simulation4";
//	EventQueue5 event_queue(10);
//	Environment::Init(sim_dir, 1, 30, 4, 5, 5, 1, &event_queue);
//	//Random::GetGenerator().advance(2);
//
//	// CREATE REGIONS ========================================================================================================
//	std::vector<double> diffision_coefficients = { 0.1, 0.1, 0.1, 0.1 };
//	std::vector<Vec3i> n_subvolumes = { Vec3i(1), Vec3i(1), Vec3i(1), Vec3i(1) };
//	double start_time = 0, time_step = 0.05;
//	int priority = 0;
//
//	shape::basic::Box box1(Vec3d(-3.5, -0.5, -0.5), Vec3d(1));
//	shape::basic::Box box2(Vec3d(-2.5, -0.5, -0.5), Vec3d(1));
//	shape::basic::Cylinder cylinder1(Vec3d(1.5, 0, 0), 0.5, 1, Axis3D::x);
//	shape::basic::Cylinder cylinder2(Vec3d(2.5, 0, 0), 0.5, 1, Axis3D::x);
//	shape::basic::Sphere sphere1(Vec3d(0, 0, 0), 2);
//
//	Environment::AddRegion(box1, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, start_time, time_step, priority);
//	Environment::AddRegion(box2, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, start_time, time_step, priority);
//	Environment::AddRegion(sphere1, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, start_time, time_step, priority);
//	Environment::AddRegion(cylinder1, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, start_time, time_step, priority);
//	Environment::AddRegion(cylinder2, microscopic::SurfaceType::Reflecting,
//		diffision_coefficients, n_subvolumes, start_time, time_step, priority);
//
//	// Create Reactions ======================================================================================================
//	ReactionManager::AddZerothOrderReaction({ 0 }, 1, { 0 });
//	ReactionManager::AddZerothOrderReaction({ 1 }, 1, { 4 });
//	ReactionManager::AddSecondOrderReaction(0, 1, { 2, 3 }, 0.5, 0.5, {2});
//
//	Environment::LinkReactionsToRegions();
//	// DEFINE RELATIONSHIPS ======================================================================================================
//	Environment::DefineRelationship(0, 1, Environment::RelationshipPriority::None,
//		microscopic::SurfaceType::None, microscopic::SurfaceType::None);
//	Environment::DefineRelationship(1, 2, Environment::RelationshipPriority::B,
//		microscopic::SurfaceType::None, microscopic::SurfaceType::None);
//	Environment::DefineRelationship(2, 3, Environment::RelationshipPriority::A,
//		microscopic::SurfaceType::None, microscopic::SurfaceType::None);
//	Environment::DefineRelationship(3, 4, Environment::RelationshipPriority::None,
//		microscopic::SurfaceType::None, microscopic::SurfaceType::None);
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
//		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>( MicroRegionIDs({ i }),
//			MoleculeIDs({ 0, 1, 2, 3 }), 0, -1, &event_queue, time_step, 
//			static_cast<int>(Environment::GetPassiveActors().size()), true, true));
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
//	//for (int i = 0; i < 1; i++)
//	//{
//	//	Environment::GetRegion(0).AddMolecule(0, { -0.4, 0, 0.1 });
//	//	Environment::GetRegion(1).AddMolecule(1, { 0.4, 0, -0.1 });
//	//	Environment::GetRegion(0).AddMolecule(2, { -0.4, 0, 0.1 });
//	//	Environment::GetRegion(1).AddMolecule(3, { 0.4, 0, -0.1 });
//	//}
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
//			auto& event = event_queue.Front();
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

//void TestEnvironment2()
//{
//	using namespace accord;
//
//	 SIMULATION
//	std::string sim_dir = "D:/dev/my_simulation3";
//	Environment::Init(sim_dir, 2, 10, 3, 2, 1);
//	EventQueue event_queue(7);
//
//	 CREATE REGIONS
//	std::vector<double> diffision_coefficients = { 1, 2, 3 };
//	std::vector<Vec3i> n_subvolumes = { Vec3i(2, 2, 2), Vec3i(1, 1, 1), Vec3i(1, 1, 1) };
//	double start_time = 0;
//	double time_step = 0.05;
//	int priority = 0;
//
//	shape::basic::Box box(Vec3d(-2, -2, -2), Vec3d(4, 4, 4));
//	shape::basic::Cylinder cylinder1(Vec3d(2, 0, 0), 2, 6, Axis3D::x);
//	shape::basic::Cylinder cylinder2(Vec3d(4, -6, 0), 1.5, 12, Axis3D::y);
//
//	Environment::GetRegions().reserve(3);
//	Environment::GetRegions().emplace_back(std::make_unique<microscopic::BoxRegion>(
//		box, diffision_coefficients, n_subvolumes, start_time, time_step, priority, 
//		&event_queue, microscopic::SurfaceType::Reflecting, 0));
//	Environment::GetRegions().emplace_back(std::make_unique<microscopic::CylinderRegion>(
//		cylinder1, diffision_coefficients, n_subvolumes, start_time, time_step, priority,
//		&event_queue, microscopic::SurfaceType::Reflecting, 1));
//	Environment::GetRegions().emplace_back(std::make_unique<microscopic::CylinderRegion>(
//		cylinder2, diffision_coefficients, n_subvolumes, start_time, time_step, priority,
//		&event_queue, microscopic::SurfaceType::Reflecting, 2));
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
//	 PLACE MOLECULES
//	for (int i = 0; i < 15; i++)
//	{
//		Environment::GetRegion(0).AddMolecule(0, { 0, 0, 0 });
//		Environment::GetRegion(0).AddMolecule(1, { 0, 0, 0 });
//		Environment::GetRegion(0).AddMolecule(2, { 0, 0, 0 });
//	}
//
//	 DEFINE REGION RELATIONSHIPS
//	Environment::GetRegion(0).AddNeighbour(Environment::GetRegion(1),
//		microscopic::SurfaceType::None, { 0, 1, 2 });
//	Environment::GetRegion(1).AddNeighbour(Environment::GetRegion(0),
//		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });
//	Environment::GetRegion(1).AddLowPriorityRelative(Environment::GetRegion(2),
//		microscopic::SurfaceType::None, { 0, 1, 2 });
//	Environment::GetRegion(2).AddHighPriorityRelative(Environment::GetRegion(1),
//		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });
//
//	 CREATE ACTORS
//	Environment::GetPassiveActors().reserve(2);
//	Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(
//		MicroRegionIDs({ 0, 1, 2 }),
//		MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 0, true, true));
//	Environment::GetPassiveActors().emplace_back(std::make_unique<BoxPassiveActor>(
//		shape::basic::Box(Vec3d(4, -2, -2), Vec3d(2, 4, 4)),
//		MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 1, true, true));
//
//	Json json_actors;
//	Json shapeless_actor;
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
//	 BEGIN SIMULATION LOOP
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
//			for (int i = 0; i < 15; i++)
//			{
//				Environment::GetRegion(0).AddMolecule(0, { 0, 0, 0 });
//				Environment::GetRegion(0).AddMolecule(1, { 0, 0, 0 });
//				Environment::GetRegion(0).AddMolecule(2, { 0, 0, 0 });
//			}
//		}
//		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
//		while (true)
//		{
//			auto& event = event_queue.Front();
//			Environment::SetTime(event.GetEventTime());
//			if (Environment::GetTime() > Environment::GetRunTime())
//			{
//				LOG_INFO("The Next Event Outside Run Time : ({})", event);
//				break;
//			}
//			LOG_INFO("Time = {}, EventID = {}, EventType = {}", Environment::GetTime(), event.GetID(), event.GetType());
//			LOG_INFO("Event:({})", event);
//			event.Run();
//		}
//	} while (Environment::NextRealisation());
//
//	LOG_INFO("Cleaning Up");
//}

//void TestEnvironment()
//{
//	using namespace accord;
//
//	Environment::Init("D:/dev/my_simulation2", 5, 10, 3, 2, 1);
//	EventQueue event_queue(6);
//
//	// REGIONS
//
//	std::vector<double> diffision_coefficients = { 1, 2, 3 };
//	std::vector<Vec3i> n_subvolumes = { Vec3i(2, 2, 2), Vec3i(1, 1, 1), Vec3i(1, 1, 1) };
//	double start_time = 0;
//	double time_step = 0.05;
//	int priority = 0;
//
//	// sim 1
//	//std::unique_ptr<microscopic::SurfaceShape> surface_shape =
//	//	std::make_unique<microscopic::SphereSurfaceShape>(Vec3d(0, 0, 0), 2);
//
//	//std::unique_ptr<microscopic::SurfaceShape> surface_shape2 =
//	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(1.5, -0.5, -0.5), Vec3d(4, 1, 1));
//
//	// sim 2
//	std::unique_ptr<microscopic::SurfaceShape> surface_shape3 =
//		std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-4, -4, -4), Vec3d(8, 8, 8));
//
//	std::unique_ptr<microscopic::SurfaceShape> surface_shape4 =
//		std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(2, -3, -3), Vec3d(2, 6, 6));
//
//	std::unique_ptr<microscopic::SurfaceShape> surface_shape5 =
//		std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-7, -7, -7), Vec3d(14, 14, 14));
//
//	// sim 3
//	std::unique_ptr<microscopic::SurfaceShape> surface_shape6 =
//		std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-4, -4, -4), Vec3d(8, 8, 8));
//
//	std::unique_ptr<microscopic::SurfaceShape> surface_shape7 =
//		std::make_unique<microscopic::CylinderSurfaceShape>(Vec3d(7, 0, 0), 6, 3, Axis3D::x);
//
//
//	// MUST RESERVE NUMBER OF REGIONS OTHERWISE EVENT IS ADDED MULTIPLE TIMES TO QUEUE
//	Environment::microscopic_regions.reserve(3);
//	// Sim 1
//	//Environment::microscopic_regions.emplace_back(
//	//	diffision_coefficients, n_subvolumes, std::move(surface_shape),
//	//	start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 0);
//	//
//	//Environment::microscopic_regions.emplace_back(
//	//	diffision_coefficients, n_subvolumes, std::move(surface_shape2),
//	//	start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 1);
//	// Sim 2
//	Environment::microscopic_regions.emplace_back(
//		diffision_coefficients, n_subvolumes, std::move(surface_shape3),
//		start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 0);
//
//	Environment::microscopic_regions.emplace_back(
//		diffision_coefficients, n_subvolumes, std::move(surface_shape4),
//		start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 1);
//
//	Environment::microscopic_regions.emplace_back(
//		diffision_coefficients, n_subvolumes, std::move(surface_shape5),
//		start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 2);
//
//	// Sim 1
//	//g_json["shapes"]["sphere"].emplace_back(shape::basic::Sphere(Vec3d(0, 0, 0), 2));
//	//g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(1.5, -0.5, -0.5), Vec3d(4, 1, 1)));
//	// Sim 2
//	g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-4, -4, -4), Vec3d(8, 8, 8)));
//	g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(2, -3, -3), Vec3d(2, 6, 6)));
//	g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-7, -7, -7), Vec3d(14, 14, 14)));
//
//	std::ofstream ofile("D:/dev/my_simulation2/regions.json");
//	ofile << JsonToString(g_json);
//	ofile.close();
//
//	for (int i = 0; i < 15; i++)
//	{
//		Environment::microscopic_regions.at(0).AddMolecule(0, { 0, 0, 0 });
//		Environment::microscopic_regions.at(0).AddMolecule(1, { 0, 0, 0 });
//		Environment::microscopic_regions.at(0).AddMolecule(2, { 0, 0, 0 });
//	}
//
//	// just pass ids and can get everything from environment
//	// sim 1
//	//Environment::microscopic_regions.at(0).AddLowPriorityRelative(Environment::microscopic_regions.at(1), 
//	//	microscopic::SurfaceType::None, { 0, 1, 2 });
//	// sim 2
//	Environment::microscopic_regions.at(0).AddHighPriorityRelative(Environment::microscopic_regions.at(1),
//		microscopic::SurfaceType::None, { 0, 1, 2 });
//	Environment::microscopic_regions.at(1).AddLowPriorityRelative(Environment::microscopic_regions.at(0),
//		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });
//	Environment::microscopic_regions.at(1).AddLowPriorityRelative(Environment::microscopic_regions.at(2),
//		microscopic::SurfaceType::None, { 0, 1, 2 });
//	Environment::microscopic_regions.at(2).AddHighPriorityRelative(Environment::microscopic_regions.at(0),
//		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });
//
//
//	// test path of single molecule
//	if (false)
//	{
//		auto a = Environment::microscopic_regions.at(0).GetGrid(0).CheckMoleculePath({ 0, 0, 0 }, { 22, 7, 9 }, 100);
//		if (a.has_value())
//		{
//			//LOG_INFO(a->GetPosition());
//		}
//
//		g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-2, -2, -2), Vec3d(4, 4, 4)));
//		g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(2, -2, -2), Vec3d(4, 4, 4)));
//		std::ofstream ofile("C:/dev/AcCoRD2/MATLAB/path.json");
//		LOG_INFO(JsonToString(g_json));
//		ofile << JsonToString(g_json);
//		ofile.close();
//		return;
//	}
//
//	// ACTORS
//	// cannot delete passive actor in vector
//	PassiveActor p1(MicroRegionIDs({ 0 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 0, true, true);
//	PassiveActor p2(MicroRegionIDs({ 1 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 1, true, true);
//	PassiveActor p3(MicroRegionIDs({ 2 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 2, true, true);
//
//	do {
//		if (Environment::GetRealisationNumber() > 0)
//		{
//			p1.NextRealisation();
//			p2.NextRealisation();
//			p3.NextRealisation();
//			
//			for (auto& region : Environment::microscopic_regions)
//			{
//				region.NextRealisation();
//			}
//
//			for (int i = 0; i < 15; i++)
//			{
//				Environment::microscopic_regions.at(0).AddMolecule(0, { 0, 0, 0 });
//				Environment::microscopic_regions.at(0).AddMolecule(1, { 0, 0, 0 });
//				Environment::microscopic_regions.at(0).AddMolecule(2, { 0, 0, 0 });
//			}
//		}
//		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
//		while (true)
//		{
//			auto& event = event_queue.Front();
//			Environment::SetTime(event.GetTime());
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
//	LOG_INFO("Cleaning Up");
//}

void TestCylinder()
{
	using namespace accord;
	using namespace accord::shape;
	if (false)
	{
		collision::Cylinder c({ -5, 0, 0 }, 5, 10, Axis3D::x);
		Vec3d origin(0, 0, 0);
		Vec3d end(50, 0, 0);
		auto collision = c.CalculateInternalCollisionData(origin, end);
		LOG_INFO(collision);

		relation::Cylinder rc({ 0, 0, 0 }, 2, 5, Axis3D::x);

		Json j;
		rc.FlattenInAxis(Axis3D::x).ToJson(j[0]);
		rc.FlattenInAxis(Axis3D::y).ToJson(j[1]);
		rc.FlattenInAxis(Axis3D::z).ToJson(j[2]);
		LOG_INFO(JsonToPrettyString(j));

		LOG_INFO(rc.GenerateBoundingBox());
		LOG_INFO(rc.IsEnvelopedBy({ {-5, -5, -5}, {11, 10, 10} }));
	}



	relation::Cylinder cylinder({ 0, -0.7, 0 }, 0.7, 2, Axis3D::y);

	relation::Sphere sphere({ 0, 0, 0 }, 0.5);

	LOG_INFO(cylinder.IsEnvelopedBy(sphere));
	LOG_INFO(cylinder.IsOverlapping(sphere));
	LOG_INFO(cylinder.IsEnveloping(sphere));
}



void TestMesoscopic()
{
	using namespace accord;
	int n_micro_regions = 0, n_meso_regions = 1, n_passive_actors = n_meso_regions + n_micro_regions, n_active_actors = 1;
	Environment::Init("D:/dev/meso_sim", 2 , 10, 3, n_micro_regions, n_meso_regions, n_passive_actors, n_active_actors, 1);
	Environment::GetMesoscopicRegions().emplace_back(Vec3d(0), 1, Vec3i(2, 1, 1), std::vector<double>{1, 1, 1}, 0, 0, 0);
	//Environment::GetMesoscopicRegions().emplace_back(Vec3d(2, 0, 0), 1, Vec3i(2, 1, 1), std::vector<double>{1, 1, 1}, 0, 0, 1);

	LOG_INFO("simulation path = {}", Environment::GetSimulationPath());
	//Environment::GetMesoscopicRegion(1).AddNeighbour(Environment::GetMesoscopicRegion(0));
	//Environment::GetMesoscopicRegion(0).AddNeighbour(Environment::GetMesoscopicRegion(1));
	

	//Environment::GetMesoscopicRegions().at(0).AddZerothOrderReaction({ 0 }, 1);
	//Environment::GetMesoscopicRegions().at(0).AddFirstOrderReaction(1, {2}, 1);
	//Environment::GetMesoscopicRegions().at(0).AddSecondOrderReaction(0, 1, { 2 }, 1);

	//ReactionManager::AddSecondOrderReaction(0, 1, { 2 }, 0, 0, 1, {}, { 0 });
	//Environment::LinkReactionsToRegions();

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
		std::make_unique<ActiveActorBox>(Vec3d(0), Vec3d(2, 1, 1)), 0, 5, 0));

	for (int i = 0; i < 0; i++)
	{
		//Environment::GetMesoscopicRegion(0).AddMolecule(i % 2, { 0.5, 0.5, 0.5 });
		Environment::GetMesoscopicRegion(0).AddMolecule(0, { 3.5, 0.5, 0.5 });
	}
	

	double time_step = 0.05;
	Environment::GetPassiveActors().reserve(Environment::GetMesoscopicRegions().size());
	LOG_INFO(Environment::GetMesoscopicRegions().size());
	for (int i = 0; i < Environment::GetMesoscopicRegions().size(); i++)
	{
		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroRegionIDs({}),
			MesoRegionIDs({ i }), MoleculeIDs({ 0, 1, 2}), 0, -1, time_step,
			static_cast<int>(Environment::GetPassiveActors().size()), true, true));
	}

	Json json_regions;
	for (auto& region : Environment::GetMesoscopicRegions())
	{
		json_regions["shapes"].emplace_back(region);
	}
	std::ofstream region_file(Environment::GetSimulationPath() + "/regions.json");
	region_file << JsonToString(json_regions);
	region_file.close();

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
			//LOG_INFO("Event:({})", event);
			event.Run();
		}
	} while (Environment::NextRealisation());
}

#include "fixed_range_int.h"
int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");       

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	using namespace accord;
	using MoleculeIDs2 = std::vector<MoleculeID2>;
	MoleculeID2::SetRange(5, 10);
	//MoleculeID2 a(11);
	MoleculeIDs2 v = {6, 7, 8, 12};
	//TestMesoscopic();

	//Event2Test();
	//TestSimpleEnvironment2();
	//ActiveActorTest();

	//TestEnvironment2();
	
	//TestEnvironment();
	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
	//accord::EventQueueTest();
	//accord::ShapeRelationTest();
	//accord::Shape3DRelationTest();
	//accord::ShapeCollisionTest();
}