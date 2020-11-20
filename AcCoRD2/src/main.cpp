#include "pch.h"

//#include "logger_test.h"
//#include "json_test.h"
//#include "random_test.h"
//#include "vec_test.h"
//#include "output_binary_test.h"
//#include "event_queue_test.h"
#include "shape_test.h"

#include "basic_box_2d.h"


#include "axis_3d.h"

class Axis3D
{
public:
	enum Type
	{
		x, y, z
	};

	constexpr Axis3D(Type type) 
		: type(type) 
	{ 

	}

	constexpr operator Type() const { return type; }

	constexpr bool operator == (Axis3D axis) const 
	{
		return type == axis.type; 
	}
	constexpr bool operator != (Axis3D axis) const 
	{
		return type != axis.type; 
	}

	std::string ToString() const
	{
		switch (type)
		{
		case Axis3D::x:
			return "x";
		case Axis3D::y:
			return "y";
		case Axis3D::z:
			return "z";
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}
private:
	Type type;
};

void to_json(accord::Json& j, Axis3D axis)
{
	j = axis.ToString();
}

template<typename OStream>
OStream& operator<<(OStream& os, const Axis3D::Type& type)
{
	return os << Axis3D::ToString(type);
}

template<typename OStream>
OStream& operator<<(OStream& os, const Axis3D& type)
{
	return os << type.ToString();
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

	//accord::Json j = accord::shape::basic::Box2D({ 0,0 }, { 10, 10 });

	//rename tests to Test...() or put in namespace test
}