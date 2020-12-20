#include "pch.h"

// KANBAN CHART =====================================================================================================================================

// DONE
// add cylinders
// change circle collision to const
// consider converting planes into single non-virtual class
// is neighbouring functions should return boolean
// only is partially neighbouring function of boxes needs to calculate area
// add as seperate function. e.g. CalculateAreaBetweenNeighbouringBoxes()
// rename relation surface shape to shape 2d
// add vector operation - (scalar)
// may need to seperate microscopic surface shape from microscopic region shapes as regions cannot be typical surfaces?
// --- currently microscopic surface shape is only for region shapes. However as regions must now be constructed using
// --- derived classes passing an invalid surface shape to a region is no longer possible.
// --- i.e. all regions shapes are surface shapes but not all surface shapes are regions shapes.
// make it easier to save region shapes in region.json. E.g. environment.saveRegions
// regions per shape to avoid unique pointer

// CANCELLED
// add clip function // wrap was clip
// add wrap function // not require atm
// add inrange function // too many variants (inclusive, exclusive, return double, return vec3d)
// consider converting cylinder into class per axis
// consider using flatten relation method for box and spheres (Flattening does not work on spheres)
// could use factory to build regions so regions dont have to be publically available in environment (factory no longer needed due to derived class)

// IN PROGRESS
// consider adding generate bounding box and rect to all shapes
// consider multiple constructors for shapes so you can generate shapes using other shapes
// add a GetBasicShape() to each shape type so you can write the basic shape of a region to json

// TO DO (Imminent)
// surface type per grid

// TO DO (Large Tasks)
// surfaces
// reactions

// TO DO (Not Imminent)
// consider passing objects into constructor via const reference to avoid including headers in headers
// ensure consistent to ToJson to_json
// check json works
// ensure consistency between vec2 and vec3
// json / spdlog should print faces of 3d shapes
// check cpp files dont have #pragma once
// NEED TO WARN IF CANNOT WRITE TO FILE / DELETE SEED FOLDER
// find location where i have repeated a scalar to construct a vec and use new scalar constructor

// BUGS
// 1. WHY WERE RECENT MOLECULES AHEAD OF EVENT TIME IF BOTH REGIONS HAVE THE SAME TIME STEP AND OCCUR
// AT THE SAME TIME?
// ANSWER: Recent molecules were being added to the next event time rather than the current one
// Confusion lies in that a region time is updated before the molecule are.
// i.e. region updates its next event time from 1s to 2s. Then at 2s the event from 1 to 2 occur. 
// At the end of the update all molecules should have caught up to 2s.
// 2. Passive Actors cannot be placed into vector as the vector cannot deconstruct.
// FIXED 19/12/20
// 3. Why are molecules reflecting too many times when a cylinder spans across another cylinder?
// Not error but a result of region walls being too close together.
// Capped number of interactions before molecule is placed at last intersection
// 4. Found bug where positions were only being written every other observation for shaped passive actors?
// FIXED 19/12/20

// RESEARCH
// custom destructor
// modules

// KANBAN CHART =====================================================================================================================================

#include "event_queue_test.h"
#include "microscopic_region2.h"
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

void TestEnvironment2()
{
	using namespace accord;

	// SIMULATION
	std::string sim_dir = "D:/dev/my_simulation3";
	Environment::Init(sim_dir, 2, 10, 3, 2, 1);
	EventQueue event_queue(7);

	// CREATE REGIONS
	std::vector<double> diffision_coefficients = { 1, 2, 3 };
	std::vector<Vec3i> n_subvolumes = { Vec3i(2, 2, 2), Vec3i(1, 1, 1), Vec3i(1, 1, 1) };
	double start_time = 0;
	double time_step = 0.05;
	int priority = 0;

	shape::basic::Box box(Vec3d(-2, -2, -2), Vec3d(4, 4, 4));
	shape::basic::Cylinder cylinder1(Vec3d(2, 0, 0), 2, 6, Axis3D::x);
	shape::basic::Cylinder cylinder2(Vec3d(4, -6, 0), 1.5, 12, Axis3D::y);

	Environment::GetRegions().reserve(3);
	Environment::GetRegions().emplace_back(std::make_unique<microscopic::BoxRegion>(
		box, diffision_coefficients, n_subvolumes, start_time, time_step, priority, 
		&event_queue, microscopic::SurfaceType::Reflecting, 0));
	Environment::GetRegions().emplace_back(std::make_unique<microscopic::CylinderRegion>(
		cylinder1, diffision_coefficients, n_subvolumes, start_time, time_step, priority,
		&event_queue, microscopic::SurfaceType::Reflecting, 1));
	Environment::GetRegions().emplace_back(std::make_unique<microscopic::CylinderRegion>(
		cylinder2, diffision_coefficients, n_subvolumes, start_time, time_step, priority,
		&event_queue, microscopic::SurfaceType::Reflecting, 2));

	Json json_regions;
	for (auto& regions : Environment::GetRegions())
	{
		json_regions["shapes"].emplace_back(regions->GetShape().GetBasicShape());
	}
	std::ofstream region_file(sim_dir + "/regions.json");
	region_file << JsonToString(json_regions);
	region_file.close();

	// PLACE MOLECULES
	for (int i = 0; i < 15; i++)
	{
		Environment::GetRegion(0).AddMolecule(0, { 0, 0, 0 });
		Environment::GetRegion(0).AddMolecule(1, { 0, 0, 0 });
		Environment::GetRegion(0).AddMolecule(2, { 0, 0, 0 });
	}

	// DEFINE REGION RELATIONSHIPS
	Environment::GetRegion(0).AddNeighbour(Environment::GetRegion(1),
		microscopic::SurfaceType::None, { 0, 1, 2 });
	Environment::GetRegion(1).AddNeighbour(Environment::GetRegion(0),
		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });
	Environment::GetRegion(1).AddLowPriorityRelative(Environment::GetRegion(2),
		microscopic::SurfaceType::None, { 0, 1, 2 });
	Environment::GetRegion(2).AddHighPriorityRelative(Environment::GetRegion(1),
		microscopic::SurfaceType::Reflecting, { 0, 1, 2 });

	// CREATE ACTORS
	std::vector<std::unique_ptr<PassiveActor>> passive_actors;
	passive_actors.reserve(2);
	passive_actors.emplace_back(std::make_unique<ShapelessPassiveActor>(
		RegionIDs({ 0, 1, 2 }), 
		MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 0, true, true));
	passive_actors.emplace_back(std::make_unique<BoxPassiveActor>(
		shape::basic::Box(Vec3d(4, -2, -2), Vec3d(2, 4, 4)),
		MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 1, true, true));

	Json json_actors;
	Json shapeless_actor;
	shapeless_actor["type"] = "none";
	for (auto& passive_actor : passive_actors)
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

	// BEGIN SIMULATION LOOP
	do {
		if (Environment::GetRealisationNumber() > 0)
		{
			for (auto& passive_actor : passive_actors)
			{
				passive_actor->NextRealisation();
			}
			for (auto& region : Environment::GetRegions())
			{
				region->NextRealisation();
			}
			for (int i = 0; i < 15; i++)
			{
				Environment::GetRegion(0).AddMolecule(0, { 0, 0, 0 });
				Environment::GetRegion(0).AddMolecule(1, { 0, 0, 0 });
				Environment::GetRegion(0).AddMolecule(2, { 0, 0, 0 });
			}
		}
		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
		while (true)
		{
			auto& event = event_queue.Front();
			Environment::SetTime(event.GetTime());
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
//	PassiveActor p1(RegionIDs({ 0 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 0, true, true);
//	PassiveActor p2(RegionIDs({ 1 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 1, true, true);
//	PassiveActor p3(RegionIDs({ 2 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 2, true, true);
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

#include "basic_shape_3d.h"
#include "passive_actor2.h"
int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");       

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	TestEnvironment2();

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