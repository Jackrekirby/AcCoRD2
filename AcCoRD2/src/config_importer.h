#pragma once
#include "pch.h"

namespace accord
{
	class JsonKeyPair;
	class ConfigImporter
	{
	public:
		ConfigImporter(std::string file_path);

		const Json& GetJson();
	private:
		Json j;
		std::vector<std::string> region_names;

		void ValidateJson();

		void ValidateShape(JsonKeyPair& shape_owner);

		size_t ValidateMicroscopicRegions(JsonKeyPair& config);

		size_t ValidateMesoscopicRegions(JsonKeyPair& config);

		size_t ValidateActiveActors(JsonKeyPair& config);

		size_t ValidatePassiveActors(JsonKeyPair& config);
	};
}