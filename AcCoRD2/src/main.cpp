#include "pch.h"
// add vector operation - (scalar)
// change circle collision to const
// add cylinders
// add clip function
// add wrap function
// NEED TO WARN IF CANNOT WRITE TO FILE / DELETE SEED FOLDER

// WHY WERE RECENT MOLECULES AHEAD OF EVENT TIME IF BOTH REGIONS HAVE THE SAME TIME STEP AND OCCUR
// AT THE SAME TIME?
// ANSWER: Recent molecules were being added to the next event time rather than the current one
// Confusion lies in that a region time is updated before the molecule are.
// i.e. region updates its next event time from 1s to 2s. Then at 2s the event from 1 to 2 occur. 
// At the end of the update all molecules should have caught up to 2s.

//#include "logger_test.h"
//#include "json_test.h"
//#include "random_test.h"
//#include "vec_test.h"
//#include "output_binary_test.h"
#include "event_queue_test.h"
//#include "shape_test.h"


#include "microscopic_region2.h"
#include "environment.h"
#include "event_queue.h"
#include "event.h"
//#include "microscopic_surface.h"
//#include "microscopic_box_surface.h"
#include "passive_actor.h"
#include "microscopic_box_surface_shape.h"
#include "microscopic_surface_shape.h"
#include "microscopic_sphere_surface_shape.h"

void TestEnvironment()
{
	using namespace accord;

	Environment::Init("D:/dev/my_simulation", 5, 10, 3, 2, 1);
	EventQueue event_queue(6);

	// REGIONS

	std::vector<double> diffision_coefficients = { 1, 2, 3 };
	std::vector<Vec3i> n_subvolumes = { Vec3i(2, 2, 2), Vec3i(1, 1, 1), Vec3i(1, 1, 1) };
	double start_time = 0;
	double time_step = 0.05;
	int priority = 0;

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-1, -1, -1), Vec3d(2, 2, 2));

	std::unique_ptr<microscopic::SurfaceShape> surface_shape =
		std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(1.5, -0.5, -0.5), Vec3d(4, 1, 1));

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-2, -2, -2), Vec3d(4, 4, 4));

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape2 =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(2, -2, -2), Vec3d(4, 4, 4));

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape2 =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-5, -5, -5), Vec3d(10, 10, 10));

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape2 =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(-5, -5, -5), Vec3d(10, 10, 10));

	//std::unique_ptr<microscopic::SurfaceShape> surface_shape3 =
	//	std::make_unique<microscopic::BoxSurfaceShape>(Vec3d(1, -2, -2), Vec3d(1, 4, 4));

	std::unique_ptr<microscopic::SurfaceShape> surface_shape2 =
		std::make_unique<microscopic::SphereSurfaceShape>(Vec3d(0, 0, 0), 2);

	// MUST RESERVE NUMBER OF REGIONS OTHERWISE EVENT IS ADDED MULTIPLE TIMES TO QUEUE
	Environment::microscopic_regions.reserve(2);
	Environment::microscopic_regions.emplace_back(
		diffision_coefficients, n_subvolumes, std::move(surface_shape),
		start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 0);

	Environment::microscopic_regions.emplace_back(
		diffision_coefficients, n_subvolumes, std::move(surface_shape2),
		start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 1);

	//Environment::microscopic_regions.emplace_back(
	//	diffision_coefficients, n_subvolumes, std::move(surface_shape3),
	//	start_time, time_step, priority, &event_queue, microscopic::SurfaceType::Reflecting, 2);

	g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(1.5, -0.5, -0.5), Vec3d(4, 1, 1)));
	g_json["shapes"]["sphere"].emplace_back(shape::basic::Sphere(Vec3d(0, 0, 0), 2));
	//g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(2, -2, -2), Vec3d(4, 4, 4)));
	//g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-5, -5, -5), Vec3d(10, 10, 10)));
	//g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-5, -5, -5), Vec3d(10, 10, 10)));
	//g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(1, -2, -2), Vec3d(1, 4, 4)));

	std::ofstream ofile("D:/dev/my_simulation/regions.json");
	ofile << JsonToString(g_json);
	ofile.close();

	for (int i = 0; i < 25; i++)
	{
		Environment::microscopic_regions.at(1).AddMolecule(0, { 0, 0, 0 });
		Environment::microscopic_regions.at(1).AddMolecule(1, { 0, 0, 0 });
	}

	// just pass ids and can get everything from environment
	Environment::microscopic_regions.at(1).AddLowPriorityRelative(Environment::microscopic_regions.at(0), 
		microscopic::SurfaceType::None, { 0, 1, 2 });
	//Environment::microscopic_regions.at(1).AddLowPriorityRelative(Environment::microscopic_regions.at(0),
		//microscopic::SurfaceType::None, { 0, 1, 2 });
	//Environment::microscopic_regions.at(0).AddMolecule(0, { 3, 3, 3 });
	//Environment::microscopic_regions.at(0).AddMolecule(0, { 3, 3, 3 });
	//Environment::microscopic_regions.at(0).AddMolecule(0, { 3, 3, 3 });
	//Environment::microscopic_regions.at(0).AddMolecule(1, { 3, 3, 3 });
	//Environment::microscopic_regions.at(0).AddMolecule(1, { 3, 3, 3 });
	//Environment::microscopic_regions.at(0).AddMolecule(2, { 3, 3, 3 });

	// test path of single molecule
	if (false)
	{
		auto a = Environment::microscopic_regions.at(0).GetGrid(0).CheckMoleculePath({ 0, 0, 0 }, { 22, 7, 9 });
		if (a.has_value())
		{
			//LOG_INFO(a->GetPosition());
		}

		g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(-2, -2, -2), Vec3d(4, 4, 4)));
		g_json["shapes"]["box"].emplace_back(shape::basic::Box(Vec3d(2, -2, -2), Vec3d(4, 4, 4)));
		std::ofstream ofile("C:/dev/AcCoRD2/MATLAB/path.json");
		LOG_INFO(JsonToString(g_json));
		ofile << JsonToString(g_json);
		ofile.close();
		return;
	}
	// ACTORS

	PassiveActor p(RegionIDs({ 0 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 0, true, true);
	PassiveActor p2(RegionIDs({ 1 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 1, true, true);
	//PassiveActor p3(RegionIDs({ 2 }), MoleculeIDs({ 0, 1, 2 }), 0, -1, &event_queue, 0.05, 2, true, true);
	//LOG_INFO(event_queue);
	//for (auto evnt : event_queue.GetEvents())
	//{
	//	LOG_INFO(*evnt);
	//}
	do {
		if (Environment::GetRealisationNumber() > 0)
		{
			p.NextRealisation();
			p2.NextRealisation();
			for (auto& region : Environment::microscopic_regions)
			{
				region.NextRealisation();
			}

			for (int i = 0; i < 25; i++)
			{
				Environment::microscopic_regions.at(1).AddMolecule(0, { 0, 0, 0 });
				Environment::microscopic_regions.at(1).AddMolecule(1, { 0, 0, 0 });
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

}

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	//using namespace accord;
	
	//shape::collision::Box b(Vec3d(-2, -2, -2), Vec3d(4, 4, 4));
	//LOG_INFO(JsonToPrettyString(b));
	//LOG_INFO(b.CalculateInternalCollisionData({ 0, 0, 0 }, { 9, 1, 0 }));
	//LOG_INFO(b.CalculateInternalCollisionData({ 0, 0, 0 }, { -7, 18, 9 }));

	TestEnvironment();
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

	//accord::Json j = accord::shape::basic::Rect({ 0,0 }, { 10, 10 });

	//rename tests to Test...() or put in namespace test
}