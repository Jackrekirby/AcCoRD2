#include "json.h"

#include <iomanip> // for std::setw
#include <sstream> // for std::stringstream

namespace accord
{
	Json g_json;

	std::string JsonToString(const Json& j)
	{
		std::stringstream os;
		os << j;
		return os.str();
	}

	std::string JsonToPrettyString(const Json& j)
	{
		std::stringstream os;
		os << std::setw(4) << j;
		return os.str();
	}
}