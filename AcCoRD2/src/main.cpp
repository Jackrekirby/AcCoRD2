#include "pch.h"

//#include "logger_test.h"
//#include "json_test.h"
//#include "random_test.h"
//#include "vec_test.h"
//#include "output_binary_test.h"
//#include "event_queue_test.h"
#include "shape_test.h"

class base
{
public:
	int x;

	base(int x) 
		: x(x)
	{

	}
};

class derived : public base
{
public:
	derived(int y)
		: base(y)
	{

	}
};

void to_json(accord::Json& j, const base& b)
{
	j = "this is base class";
}

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

	//set run time global Logger level
	accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
	//accord::EventQueueTest();
	//accord::ShapeRelationTest();
	accord::Shape3DRelationTest();

	accord::Json j = derived(7);

	LOG_INFO(accord::JsonToPrettyString(j));

	//accord::Json j = accord::shape::basic::Rect({ 0,0 }, { 10, 10 });

	//rename tests to Test...() or put in namespace test
}