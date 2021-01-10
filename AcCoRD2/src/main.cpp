#include "pch.h"

// Questions
// Can zero reaction molecules be placed inside a child region?
// Does the volume used to calculaet the next reaciton time include that of children as well?
// I assume reactions in a region only start occuring at a regions start time?
// if a molecule is generated and is inside a hgih prioprity region should have flag which specifies if molecule placement should fail
// If the molecule can participate in multiple non-surface first order reactions, then the probability of reaction c occurring is[15, Eq. (14)].
// Is this for reactions within the same region, or all regions?
// can a reaction have multiple products of the same molecule type and what format is it?
// couldnt products be placed outside the region if unbind radius is huge?
// Can a point active actor with random release time be a point source because release time calcualtion includes volume of actor
// for active active with random release times it says only 1 molecule is released per release time, does that mean then only one molecule type can be
// released from an active actor at once?
// If an active actor is defined over multiple regions is a region randomly selected to place a molecule in based on it volume, and does the volume
// ignore that removed by child regions?
// can an active actor record its release times? (currently only passive)
// active actors with a random release time do not have a bit sequence?
// how did u implement the number of event actions. Do you always set max actions by doing simulation_length / time_step
// for an active actor which is a surface do you use the area instead of the volume to calaculate the release_coefficient for a random time active actor
// When you update diffusion propensities do you return the delta?
// When you go through possible reactions you can store them in a tree like structure to reduce searches further.
// did you use a math vec struct?
// do you store a list of objects to be updated when a molecule count is updated?
// can i talk about what makes the original code < ..
// when molecules are added to a subvolume outside of its action time if the propensity updated every time a molecule is added or for example
// do you let multiple molecules be added then only update those subvolumes requiring an update
// updating event time does not work if time has not changed and/or old propensity = 0; 
// --- SetTime(current_time + (old_propensity / reaction_propensity) * (time - current_time));

// Investigate
// If a regions start time is at 0.5 seconds and time step is 1 then shouldnt the regions first event be at 1.5 seconds?
// how to stop two basic shapes being generated when microscopic surface shapes inherit from generating and collision shapes (virtual inheritance)
// if the reaction rate is for example 1 is that 1 molecule produced per second or all products per second?
// when molecules are added to regions each high priority neighbour should be checked to see if molecules can be added to them.
// Alot of relation checking could be done outside the class by an external class which simply returns a vector of regions which match.
// E.g. Regions* = RelationFinder.GetRegionsWhichOverlap(shape). Then ActiveActor.AddRegions(Regions*)
// E.g. RelationFinder.IsRelationShipValid(region_a, region_b, relationship)
// could stick I/O on a seperate thread so can write to binary files which simulation runs next step. Would require a copy of the position vector or make it lockable

// Learning Plan
// Learnt the importance of reserving as allowing a vector to resize invalidates pointers.
// Learnt how to use visual studio performance profiler
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
// add zeroth order reactions for microscopic regions
// rename grid, subvolume and region 2 to _
// need to find where i use iterator loop and set iterator to another. It may be it& = it and may need to be it = it + 1. (LINK GRIDS?)
// make all shapes have virtual inheritance of basic shapes
// consider redoing reactions with reaction manager as all regions import reactions from it
// split meso classes
// ensure consistent reaction_factor reaction_coefficient_naming
// rename events to reactions

// CANCELLED
// add clip function // wrap was clip
// add wrap function // not require atm
// add inrange function // too many variants (inclusive, exclusive, return double, return vec3d)
// consider converting cylinder into class per axis
// consider using flatten relation method for box and spheres (Flattening does not work on spheres)
// could use factory to build regions so regions dont have to be publically available in environment (factory no longer needed due to derived class)
// update test envrionments to new format (consider switch statement?) (format keep changing)
// abstract event queue (not easily possible, offers much more flexibility without abstraction)


// IN PROGRESS
// consider adding generate bounding box and rect to all shapes
// consider multiple constructors for shapes so you can generate shapes using other shapes
// add a GetBasicShape() to each shape type so you can write the basic shape of a region to json

// TO DO (next)
// seperate public and private functions, particularly for active actors ane mesoscopic classes

// TO DO (Imminent)
// add subvolume neighbour check
// add subvolume removal / overlap check
// add meso-micro transition
// add set event time past simulation time.
// add generation checking to regions so youngest regions can be sorted first for collision checking 
// --- (important for surfaces ! surfaces should always be checked first and assume surfaces wont be within surface)
// add != vec checks
// add scalar boolean checks for vector
// add error checking for ids (and other times when creating vectors)
// avoid requiring other types, instead pass arguments with run function. A child should be unaware of its parent as much as possible
// add function vector<Grid*> GetProductsGrids(vector ids)
// ability to add multiple of a type of reactant
// Need to remove unnecessary headers by pointing to seperate variables instead of 
// rename GetTime() to GetEventTime()
// surface type per grid
// instead of saving no shapes for shapeless regions save all the regions which the observer links to. Will require reformatting.
// Reformat actor json to allow for multiple shapes per actor.
// Make base reaction class with derived VolumeReaction and SurfaceReaction

// TO DO (Large Tasks)
// surfaces - reaction surfaces (first order), membranes, adsorpsion, absorption 
// active actors
// reactions

// TO DO (Not Imminent)
// add surface and shape3d relation checking (isneighbouring, isenvelopedby)
// add default cycles for check molecule path
// could break environment class up into RelationShipManager
// consider adding limited_vectors which are vectors where only certain ints upto a given value are allowed.
// consider adding fixed_vectors which are vectors which have fixed max capacity.
// MAY be able to make second order reactions more efficient by seperating links between internal and external subvolumes
// check whether reactions can be defined in non ascending order
// make functions more descriptive (GetRegions and GetRegionIDs)
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
	EventQueue5 event_queue(3);
	Environment::Init(sim_dir, 1, 1, 4, 1, 1, 0, 1, &event_queue);
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
	//	{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 1}, n_modulation_bits, Environment::GetFilePath() + "a1_b.bin", release_molecules,
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
		bit_probability, n_modulation_bits, Environment::GetFilePath() + "a1_b.bin",
		release_molecules, modulation_strength, Environment::GetRegions({ 0 }),
		std::make_unique<ActiveActorBox>(Vec3d(-1), Vec3d(2)),
		start_time, 5, 0));

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
		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(RegionIDs({ i }),
			MoleculeIDs({ 0, 1, 2, 3 }), 0, -1, time_step,
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
			auto& event = event_queue.Front();
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
//		Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>( RegionIDs({ i }),
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
//		RegionIDs({ 0, 1, 2 }),
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



void TestMesoscopic()
{
	using namespace accord;
	EventQueue5 event_queue(1);
	Environment::Init("mesosimulation", 1, 5, 1, 0, 0, 0, 1, &event_queue);
	mesoscopic::Region region(Vec3d(0), 1, Vec3d(2, 2, 1), {1, 1, 1}, 0, 0, 0);
	
	event_queue.Add(&region);
	region.LinkSiblingSubvolumes();

	region.AddSubvolumesToQueue();

	for (int i = 0; i < 6; i++)
	{
		region.AddMolecule(i % 3, { 1, 2, 2 });
	}
	
	//LOG_INFO("next event = {}", event_queue.Front());
	//LOG_INFO("region event time = {}, ", region.GetEventTime());

	

	//LOG_INFO(event_queue.Front());

	do {
		LOG_INFO("Realisation {}", Environment::GetRealisationNumber());
		while (true)
		{
			//region.Print();
			auto& event = event_queue.Front();
			Environment::SetTime(event.GetEventTime());
			if (Environment::GetTime() > Environment::GetRunTime())
			{
				break;
			}
			LOG_INFO("Event:({})", event);
			event.Run();
		}
	} while (Environment::NextRealisation());
}


int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %s:%# %!() %v");
	//accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");       

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	TestMesoscopic();

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