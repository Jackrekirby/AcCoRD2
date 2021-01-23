#pragma once
#include "pch.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

#include "basic_box.h"
#include "basic_sphere.h"
#include "basic_cylinder.h"

namespace accord
{
	class JsonKeyPair;
	class ConfigImporter
	{
	public:
		ConfigImporter(std::string file_path);

		class RegionIDList
		{
		public:
			MicroscopicRegionIDs microscopic_ids;
			MesoscopicRegionIDs mesoscopic_ids;
		};

		class OptionalShapes
		{
		public:
			enum class Shape
			{
				Box, Sphere, Cylinder
			};
			Shape shape;
			std::optional<shape::basic::Box> box;
			std::optional<shape::basic::Sphere> sphere;
			std::optional<shape::basic::Cylinder> cylinder;
		};
	private:
		Json j;
		std::vector<std::string> region_names;
		std::vector<std::string> microscopic_region_names;
		std::vector<std::string> mesoscopic_region_names;
		size_t n_molecule_types;
		int max_molecule_id;

		// Check JSON Input files contains correct variables, types, and ranges

		void ValidateJson();

		void ValidateShape(JsonKeyPair& shape_owner);

		size_t ValidateMicroscopicRegions(JsonKeyPair& config);

		size_t ValidateMesoscopicRegions(JsonKeyPair& config);

		size_t ValidateActiveActors(JsonKeyPair& config);

		size_t ValidatePassiveActors(JsonKeyPair& config);

		void ValidateRelations(JsonKeyPair& config);

		void ValidateZerothOrderReactions(JsonKeyPair& config);

		void ValidateFirstOrderReactions(JsonKeyPair& config);

		void ValidateSecondOrderReactions(JsonKeyPair& config);

		// Transferring JSON to Environment Class

		std::optional<int> GetIndexOfStringInStrings(const std::string& key, const std::vector<std::string>& strings);

		RegionIDList GetRegionIDsFromStrings(std::vector<std::string> region_names);

		OptionalShapes CreateShape(const Json& shape);


		void CreateEnvironment();

		void CreateMicroscopicRegions();

		void CreateMesoscopicRegion();

		void CreatePassiveActors();

		void CreateActiveActors();

		void CreateRelationships();

		void CreateReactions();
	};




}