#include "json_test.h"
#include "json.h"
#include "logger.h"

#include <fstream>

namespace accord
{
	void JsonTest()
	{
		// test global json object
		g_json["key"] = "index";
		g_json["array"] = { 1, 2, 3, 4, 5 };

		LOG_INFO("Json in normal format: {}", JsonToString(g_json));

		// test correct array pretty format using #define JSON_SINGLE_LINE_PRETTY_ARRAY
		LOG_INFO("Json in pretty format: {}", JsonToPrettyString(g_json));
		
		std::ofstream json_file("logs/json_test.json");
		json_file << JsonToPrettyString(g_json);
		json_file.close();
	}
} // namespace accord