#pragma once
#include "pch.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

#include "basic_box.h"
#include "basic_sphere.h"
#include "basic_cylinder.h"
#include "basic_rect_surface.h"
#include "basic_circle_surface.h"

namespace accord
{
	class JsonKeyPair;
	class ConfigImporter
	{
	public:
		ConfigImporter(std::string file_path);

		const Json& GetJson();

		class RegionIDList
		{
		public:
			MicroscopicRegionIDs microscopic_ids;
			MesoscopicRegionIDs mesoscopic_ids;
		};

		class OptionalShapes
		{
		public:
			OptionalShapes();

			enum class Shape
			{
				Box, Sphere, Cylinder, RectSurface, CircleSurface, Point, None
			};

			Shape shape;
			std::optional<shape::basic::Box> box;
			std::optional<shape::basic::Sphere> sphere;
			std::optional<shape::basic::Cylinder> cylinder;
			std::optional<shape::basic::RectSurface> rect_surface;
			std::optional<shape::basic::CircleSurface> circle_surface;
			std::optional<Vec3d> point;
		};
	private:
		Json j;
		std::vector<std::string> region_names;
		std::vector<std::string> microscopic_region_names;
		std::vector<std::string> mesoscopic_region_names;
		size_t n_molecule_types;
		int max_molecule_id;

		// Check JSON Input files contains correct variables, types, and ranges

		Json GetReferencedValue(const std::string& reference);

		void ReplaceReferenceValues(Json& element);

		void ValidateJson();

		void ValidateShape(JsonKeyPair& shape_owner);

		void ValidateMicroscopicRegions(JsonKeyPair& config);

		void ValidateMicroscopicSurfaces(JsonKeyPair& config);

		void ValidateMesoscopicRegions(JsonKeyPair& config);

		void ValidateActiveActors(JsonKeyPair& config);

		void ValidatePassiveActors(JsonKeyPair& config);

		void ValidateRelations(JsonKeyPair& config);

		void ValidateZerothOrderReactions(JsonKeyPair& config);

		void ValidateFirstOrderReactions(JsonKeyPair& config);

		void ValidateSecondOrderReactions(JsonKeyPair& config);

		// Transferring JSON to Environment Class

		std::optional<int> GetIndexOfStringInStrings(const std::string& key, const std::vector<std::string>& strings);

		RegionIDList GetRegionIDsFromStrings(std::vector<std::string> region_names);

		OptionalShapes CreateShape(const Json& shape);

		struct SurfaceShape
		{
			SurfaceShape(bool is_surface, const std::string& shape);
			bool is_surface;
			std::string shape;
		};

		SurfaceShape SplitShapeName(const std::string& shape);


		void CreateEnvironment();

		void CreateMicroscopicRegions();

		void CreateMicroscopicSurfaces();

		void CreateMesoscopicRegion();

		void CreatePassiveActors();

		void CreateActiveActors();

		void CreateRelationships();

		void CreateReactions();
	};




}