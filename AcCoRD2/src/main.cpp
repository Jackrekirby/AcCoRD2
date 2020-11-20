#include "pch.h"

//#include "logger_test.h"
//#include "json_test.h"
//#include "random_test.h"
//#include "vec_test.h"
//#include "output_binary_test.h"
//#include "event_queue_test.h"
#include "shape_test.h"

#include "basic_box_2d.h"

class Fruit
{
public:
	enum Value : uint8_t
	{
		Apple,
		Pear,
		Banana,
		Strawberry
	};

	Fruit() = default;
	constexpr Fruit(Value aFruit) : value(aFruit) { }


	operator Value() const { return value; }  // Allow switch and comparisons.
											  // note: Putting constexpr here causes
											  // clang to stop warning on incomplete
											  // case handling.
	explicit operator bool() = delete;        // Prevent usage: if(fruit)

	constexpr bool operator==(Fruit a) const { return value == a.value; }
	constexpr bool operator!=(Fruit a) const { return value != a.value; }

	constexpr bool IsYellow() const { return value == Banana; }

private:
	Value value;
};


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
	accord::ShapeRelationTest();

	//accord::Json j = accord::shape::basic::Box2D({ 0,0 }, { 10, 10 });

	//rename tests to Test...() or put in namespace test
}