#include "pch.h"

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
#include "microscopic_surface.h"
#include "microscopic_box_surface.h"

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	using namespace accord;

	Random::SetSeed();
	EventQueue event_queue(3);

	std::vector<double> diffision_coefficients = { 1, 2, 3 };
	std::vector<Vec3i> n_subvolumes = { Vec3i(1, 1, 1), Vec3i(1, 1, 1), Vec3i(1, 1, 1) };
	double start_time = 0;
	int priority = 0;

	std::unique_ptr<microscopic::Surface> surface = 
		std::make_unique<microscopic::BoxSurface>(Vec3d( 0, 0, 0 ), Vec3d(10, 10, 10), 
			microscopic::Surface::Type::None);

	microscopic::Region2 r(diffision_coefficients, n_subvolumes, std::move(surface), start_time, priority, &event_queue);


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