#include "pch.h"
#include "config_importer.h"
#include "json_key_pair.h"
#include "environment.h"
#include <fstream>
// construction classes
#include "basic_cylinder.h"
#include "basic_sphere.h"
#include "collision_cylinder.h"
#include "relation_cylinder.h"
#include "relation_sphere.h"

#include "shapeless_passive_actor.h"

#include "environment.h"
#include "event_queue.h"
#include "event.h"

#include "passive_actor.h"
#include "shapeless_passive_actor.h"
#include "shaped_passive_actor.h"
#include "passive_actor_box_shape.h"
#include "passive_actor_cylinder_shape.h"
#include "passive_actor_sphere_shape.h"

#include "microscopic_region.h"
#include "microscopic_region_shape.h"
#include "microscopic_box_region.h"
#include "microscopic_cylinder_region.h"
#include "microscopic_sphere_region.h"

#include "reaction_manager.h"
#include "basic_shape_3d.h"

#include "active_actor_shape.h"
#include "active_actor_random_time.h"
#include "active_actor_non_random.h"
#include "active_actor_random_bits.h"

#include "mesoscopic_region.h"

#include "active_actor_box.h"
#include "active_actor_rect_surface.h"
#include "active_actor_cylinder.h"
#include "active_actor_sphere.h"
#include "active_actor_circle_surface.h"
#include "active_actor_box_surface.h"
#include "active_actor_sphere_surface.h"
#include "active_actor_cylinder_surface.h"

#include "microscopic_rect_surface_shape.h"
#include "microscopic_box_surface_shape.h"
#include "microscopic_circle_surface_shape.h"
#include "microscopic_sphere_surface_shape.h"
#include "microscopic_cylinder_surface_shape.h"
#include "active_actor_point.h"

#include "microscopic_surface.h"
#include "microscopic_high_priority_relative.h"
#include "microscopic_low_priority_relative.h"
#include "microscopic_neighbour_relative.h"

namespace accord
{
	ConfigImporter::ConfigImporter(std::string file_path)
		: n_molecule_types(0)
	{
		// Check file path is valid
		std::ifstream i(file_path);
		if (!i.is_open())
		{
			std::cout << fmt::format("[ERROR] Could not open config file <{}>\n", file_path);
			throw std::exception();
		}
		try
		{
			i >> j;
		}
		catch (Json::parse_error& e)
		{
			std::cout << fmt::format("[ERROR] Message: {} \nException id: {}\nByte position of error: {}", e.what(), e.id, e.byte);
			throw std::exception();
		}

		std::string log_filepath;
		if (j.contains("SaveToFolder"))
		{
			if (j["SaveToFolder"].is_string())
			{
				log_filepath = j["SaveToFolder"].get<std::string>() + "/log.txt";
				std::cout << fmt::format("[INFO] Logging to file: {}\n", log_filepath);
			}	
		}

		if (log_filepath.empty())
		{
			std::cout << fmt::format("[ERROR] Config file must provide key: SaveToFolder\n");
			throw std::exception();
		}

		accord::Logger::Initialise(log_filepath, "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v");
		accord::Logger::GetLogger()->set_level(spdlog::level::info);

		ReplaceReferenceValues(j);
		LOG_INFO("Validating Config File <{}>", file_path);
		ValidateJson();
		CreateEnvironment();
	}

	const Json& ConfigImporter::GetJson()
	{
		return j;
	}

	Json ConfigImporter::GetReferencedValue(const std::string& reference)
	{
		Json output = j;
		size_t pos = 0;
		std::string token;
		std::string s = reference;
		while ((pos = s.find(':')) != std::string::npos) {
			token = s.substr(0, pos);
			//LOG_INFO("token = {}", token);
			if (output.contains(token))
			{
				output = output[token];
			}
			else
			{
				LOG_ERROR("Attepting to access non existent field {}, using reference {}", token, reference);
				throw std::exception();
			}
			s.erase(0, pos + 1);
		}

		//LOG_INFO("last token = {}", s);
		if (output.contains(s))
		{
			output = output[s];
		}
		else
		{
			LOG_ERROR("Attepting to access non existent field {}, using reference {}", s, reference);
			throw std::exception();
		}
		return output;
	}

	void ConfigImporter::ReplaceReferenceValues(Json& element)
	{
		for (auto& subelement : element)
		{
			if (subelement.is_string())
			{
				//LOG_INFO("Is String");
				std::string value = subelement.get<std::string>();
				//LOG_INFO(value);
				if (!value.empty() && value.at(0) == '@')
				{
					std::string key = value.substr(1, std::string::npos);
					//LOG_WARN("Key = {}", key);
					subelement = GetReferencedValue(key);
				}
			}
			else if (subelement.is_structured())
			{
				//LOG_INFO("Is Structure");
				ReplaceReferenceValues(subelement);
			}
		}
	}

	void ConfigImporter::ValidateJson()
	{
		JsonKeyPair config(j);
		config.Add("SaveToFolder").IsString();
		config.Add("NumberOfRealisations").IsInt().IsPositive();
		config.Add("FinalSimulationTime").IsNumber().IsPositive();
		config.Add("RandomNumberSeed").IsInt().IsPositive();
		n_molecule_types = config.Add("NumberOfMoleculeTypes").IsInt().IsPositive().GetJson().get<size_t>();
		max_molecule_id = static_cast<int>(n_molecule_types) - 1;
		MoleculeID::SetNumIDs(static_cast<int>(n_molecule_types));

		ValidateMicroscopicRegions(config);
		ValidateMicroscopicSurfaces(config);
		ValidateMesoscopicRegions(config);
		ValidateActiveActors(config);
		ValidatePassiveActors(config);
		ValidateRelations(config);
		ValidateZerothOrderReactions(config);
		ValidateFirstOrderReactions(config);
		ValidateSecondOrderReactions(config);
	}

	void ConfigImporter::ValidateShape(JsonKeyPair& shape)
	{
		JsonKeyPair shape_type = shape.Add("Type").IsString();
		std::string type_str = shape_type.GetJson().get<std::string>();
		type_str = SplitShapeName(type_str).shape;
		if (type_str == "Box")
		{
			shape.Add("Origin").IsArrayOfNumbers().HasSize(3);
			shape.Add("Length").IsArrayOfNumbers().HasSize(3).IsPositive();
		}
		else if (type_str == "Sphere")
		{
			shape.Add("Centre").IsArrayOfNumbers().HasSize(3);
			shape.Add("Radius").IsNumber().IsPositive();
		}
		else if (type_str == "Cylinder")
		{
			shape.Add("BaseCentre").IsArrayOfNumbers().HasSize(3);
			shape.Add("Radius").IsNumber().IsPositive();
			shape.Add("Length").IsNumber().IsPositive();
			shape.Add("Axis").IsString().IsOneOf<std::string>({ "X", "Y", "Z" });
		}
		else if (type_str == "RectSurface")
		{
			shape.Add("Origin").IsArrayOfNumbers().HasSize(3);
			shape.Add("Length").IsArrayOfNumbers().HasSize(3).IsNonNegative().ExactNumMatchValue(0.0, 1);
		}
		else if (type_str == "CircleSurface")
		{
			shape.Add("Centre").IsArrayOfNumbers().HasSize(3);
			shape.Add("Radius").IsNumber().IsPositive();
			shape.Add("Axis").IsString().IsOneOf<std::string>({ "X", "Y", "Z" });
		}
		else if (type_str == "Point")
		{
			shape.Add("Origin").IsArrayOfNumbers().HasSize(3);
		}
		else
		{
			LOG_ERROR("The field <{}> expected value of \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", shape_type.Log(), type_str);
			throw std::exception();
		}
	}

	void ConfigImporter::ValidateMicroscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MicroscopicRegions"))
		{
			JsonKeyPair microscopic_regions = config.Add("MicroscopicRegions").IsArray();
			size_t n = microscopic_regions.GetArraySize();
			MicroscopicRegionID::SetNumIDs(static_cast<int>(n));

			for (size_t i = 0; i < n; i++)
			{
				microscopic_regions.SetIndex(i);

				JsonKeyPair name = microscopic_regions.Add("Name").IsString();
				region_names.emplace_back(name.GetJson().get<std::string>());
				microscopic_region_names.emplace_back(name.GetJson().get<std::string>());

				microscopic_regions.Add("SurfaceTypes").IsArrayOfStrings().HasSize(n_molecule_types);
				microscopic_regions.Add("DiffusionCoefficients").IsArrayOfNumbers().HasSize(n_molecule_types);
				JsonKeyPair number_of_subvolumes = microscopic_regions.Add("NumberOfSubvolumes").IsArrayOfInts().HasSize(3);
				microscopic_regions.Add("TimeStep").IsNumber().IsPositive();
				microscopic_regions.Add("Priority").IsInt();

				JsonKeyPair shape_object = microscopic_regions.Add("Shape").IsObject();
				ValidateShape(shape_object);
			}
		}
	}

	void ConfigImporter::ValidateMicroscopicSurfaces(JsonKeyPair& config)
	{
		if (config.IsKey("MicroscopicSurfaces"))
		{
			JsonKeyPair surface = config.Add("MicroscopicSurfaces").IsArray();
			size_t n = surface.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				surface.SetIndex(i);
				surface.Add("SurfaceDirection").IsString().IsOneOf<std::string>({ "Internal", "External", "Both" });
				surface.Add("SurfaceTypes").IsArrayOfStrings().HasSize(n_molecule_types);
				surface.Add("AddToRegions").IsArrayOfStrings().IsEachOneOf(microscopic_region_names);
				surface.Add("IsOnRegionSurface").IsBool();
				JsonKeyPair shape_object = surface.Add("Shape").IsObject();
				ValidateShape(shape_object);
			}
		}
	}

	void ConfigImporter::ValidateMesoscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MesoscopicRegions"))
		{
			JsonKeyPair mesoscopic_regions = config.Add("MesoscopicRegions").IsArray();
			size_t n = mesoscopic_regions.GetArraySize();
			MesoscopicRegionID::SetNumIDs(static_cast<int>(n));

			for (size_t i = 0; i < n; i++)
			{
				mesoscopic_regions.SetIndex(i);
				JsonKeyPair name = mesoscopic_regions.Add("Name").IsString();
				region_names.emplace_back(name.GetJson().get<std::string>());
				mesoscopic_region_names.emplace_back(name.GetJson().get<std::string>());

				mesoscopic_regions.Add("Origin").IsArrayOfNumbers().HasSize(3);
				mesoscopic_regions.Add("SubvolumeLength").IsNumber().IsPositive();
				mesoscopic_regions.Add("NumberOfSubvolumes").IsArrayOfInts().HasSize(3).IsPositive();
				mesoscopic_regions.Add("DiffusionCoefficients").IsArrayOfNumbers().HasSize(n_molecule_types);
				mesoscopic_regions.Add("Priority").IsInt();
			}
		}
	}

	void ConfigImporter::ValidateActiveActors(JsonKeyPair& config)
	{
		if (config.IsKey("ActiveActors"))
		{
			JsonKeyPair active_actors = config.Add("ActiveActors");
			active_actors.IsArray();
			size_t n = active_actors.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				active_actors.SetIndex(i);
				active_actors.Add("StartTime").IsNumber().IsNonNegative();
				active_actors.Add("Priority").IsInt();
				active_actors.Add("ActionInterval").IsNumber().IsPositive();
				active_actors.Add("ReleaseInterval").IsNumber().IsPositive();
				active_actors.Add("ModulationStrength").IsInt().IsPositive();
				active_actors.Add("MoleculeTypesToRelease").IsArrayOfInts().HasSize(n_molecule_types);

				if (active_actors.IsKey("RegionsToActIn"))
				{
					active_actors.Add("RegionsToActIn").IsArrayOfStrings().IsEachOneOf(region_names);
				}
				
				if (active_actors.IsKey("Shape"))
				{
					JsonKeyPair shape_object = active_actors.Add("Shape").IsObject();
					ValidateShape(shape_object);
				}

				if(!active_actors.IsKey("Shape") && !active_actors.IsKey("RegionsToActIn"))
				{
					LOG_ERROR("The object <{}> expected field of \"RegionsToActIn\" and/or \"Shape\" but neither exist", active_actors.Log());
					throw std::exception();
				}
				
				JsonKeyPair type = active_actors.Add("Type").IsString();
				std::string type_str = type.GetJson().get<std::string>();
				if (type_str == "RandomTime")
				{
				}
				else if (type_str == "RandomBits")
				{
					active_actors.Add("SymbolSize").IsInt().IsPositive();
					active_actors.Add("SlotInterval").IsNumber().IsPositive();
					active_actors.Add("BitProbability").IsNumber().IsInRange(0, 1);
				}
				else if (type_str == "NonRandom")
				{
					active_actors.Add("SymbolSize").IsInt().IsPositive();
					active_actors.Add("SlotInterval").IsNumber().IsPositive();
					active_actors.Add("BitSequence").IsArrayOfInts().IsInRange(0, 1);
				}
				else
				{
					LOG_ERROR("The field <{}> expected value of \"RandomTime\", \"RandomBits\" or \"NonRandom\" but was \"{}\"", type.Log(), type_str);
					throw std::exception();
				}
			}
		}
	}

	void ConfigImporter::ValidatePassiveActors(JsonKeyPair& config)
	{
		if (config.IsKey("PassiveActors"))
		{
			if (j.contains("ObserveEachRegion") && j["ObserveEachRegion"].get<bool>())
			{
				JsonKeyPair passive_actors = config.Add("PassiveActors");
				passive_actors.IsObject();
				passive_actors.Add("StartTime").IsNumber().IsNonNegative();
				passive_actors.Add("Priority").IsInt();
				passive_actors.Add("TimeStep").IsNumber().IsPositive();
				passive_actors.Add("RecordPositions").IsBool();
				passive_actors.Add("RecordObservationTime").IsBool();
			}
			else
			{
				JsonKeyPair passive_actors = config.Add("PassiveActors");
				passive_actors.IsArray();
				size_t n = passive_actors.GetArraySize();

				for (size_t i = 0; i < n; i++)
				{
					passive_actors.SetIndex(i);
					passive_actors.Add("StartTime").IsNumber().IsNonNegative();
					passive_actors.Add("Priority").IsInt();
					passive_actors.Add("TimeStep").IsNumber().IsPositive();
					passive_actors.Add("RecordPositions").IsBool();
					passive_actors.Add("RecordObservationTime").IsBool();
					passive_actors.Add("MoleculeTypesToObserve").IsArrayOfInts().IsInRange(0, max_molecule_id);

					if (passive_actors.IsKey("RegionsToObserve"))
					{
						passive_actors.Add("RegionsToObserve").IsArrayOfStrings().IsEachOneOf(region_names);
					}
					else if (passive_actors.IsKey("Shape"))
					{
						JsonKeyPair shape_object = passive_actors.Add("Shape").IsObject();
						ValidateShape(shape_object);
					}
					else
					{
						LOG_ERROR("<{}> expected field \"RegionsToObserve\", or \"Shape\" but neither exists", passive_actors.Log());
						throw std::exception();
					}
				}
			}
		}
	}

	void ConfigImporter::ValidateRelations(JsonKeyPair& config)
	{
		if (config.IsKey("Relationships"))
		{
			JsonKeyPair relationships = config.Add("Relationships");
			relationships.IsArray();
			size_t n = relationships.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				relationships.SetIndex(i);

				relationships.Add("RegionA").IsString().IsOneOf(region_names);
				relationships.Add("RegionB").IsString().IsOneOf(region_names);
				relationships.Add("Priority").IsString().IsOneOf<std::string>({"A", "B", "None"});;	

				std::string region_a_name = relationships.Add("RegionA").GetJson().get<std::string>();
				std::string region_b_name = relationships.Add("RegionB").GetJson().get<std::string>();
				RegionIDList region_list = GetRegionIDsFromStrings({ region_a_name , region_b_name });

				if (region_list.mesoscopic_ids.empty())
				{
					// microscopic_relationship
					std::vector<std::string> surface_types = { "Absorbing", "Adsorbing", "Membrane", "Reflecting", "None" };

					if (relationships.IsKey("SurfaceTypes"))
					{
						relationships.Add("SurfaceTypes").IsArrayOfStrings().IsEachOneOf(surface_types);
					}
					else if (relationships.IsKey("AToBSurfaceTypes") && relationships.IsKey("BToASurfaceTypes"))
					{
						relationships.Add("AToBSurfaceTypes").IsArrayOfStrings().IsEachOneOf(surface_types);
						relationships.Add("BToASurfaceTypes").IsArrayOfStrings().IsEachOneOf(surface_types);
					}
					else
					{
						LOG_ERROR("<{}> expected field \"SurfaceTypes\", or \"AToBSurfaceTypes\" and  \"BToASurfaceTypes\" but neither exists", relationships.Log());
						throw std::exception();
					}
				}
			}
		}
	}

	void ConfigImporter::ValidateZerothOrderReactions(JsonKeyPair& config)
	{
		//LOG_INFO("n_molecule_types = {}", n_molecule_types);
		if (config.IsKey("ZerothOrderReactions"))
		{
			JsonKeyPair reactions = config.Add("ZerothOrderReactions").IsArray();
			size_t n = reactions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				reactions.SetIndex(i);

				reactions.Add("Products").IsArrayOfInts().HasSize(n_molecule_types).IsNonNegative();
				reactions.Add("ReactionRate").IsNumber().IsPositive();
				reactions.Add("OccurInRegions").IsArrayOfStrings().IsEachOneOf(region_names);
			}
		}
	}

	void ConfigImporter::ValidateFirstOrderReactions(JsonKeyPair& config)
	{
		if (config.IsKey("FirstOrderReactions"))
		{
			JsonKeyPair reactions = config.Add("FirstOrderReactions");
			reactions.IsArray();
			size_t n = reactions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				reactions.SetIndex(i);
				reactions.Add("Reactant").IsInt().IsInRange(0, max_molecule_id);
				reactions.Add("Products").IsArrayOfInts().HasSize(n_molecule_types).IsNonNegative();
				reactions.Add("ReactionRate").IsNumber().IsPositive();
				reactions.Add("OccurInRegions").IsArrayOfStrings().IsEachOneOf(region_names);
			}
		}
	}

	void ConfigImporter::ValidateSecondOrderReactions(JsonKeyPair& config)
	{
		if (config.IsKey("SecondOrderReactions"))
		{
			JsonKeyPair reactions = config.Add("SecondOrderReactions");
			reactions.IsArray();
			size_t n = reactions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				reactions.SetIndex(i);
				reactions.Add("ReactantA").IsInt().IsInRange(0, max_molecule_id);
				reactions.Add("ReactantB").IsInt().IsInRange(0, max_molecule_id);
				reactions.Add("Products").IsArrayOfInts().HasSize(n_molecule_types).IsNonNegative();
				reactions.Add("ReactionRate").IsNumber().IsPositive();
				reactions.Add("OccurInRegions").IsArrayOfStrings().IsEachOneOf(region_names);
				reactions.Add("BindingRadius").IsNumber().IsNonNegative();
				reactions.Add("UnBindingRadius").IsNumber().IsNonNegative();
			}
		}
	}



	std::optional<int> ConfigImporter::GetIndexOfStringInStrings(const std::string& key, const std::vector<std::string>& strings)
	{
		auto key_it = std::find(strings.begin(), strings.end(), key);
		if (key_it != strings.end())
		{
			return static_cast<int>(key_it - strings.begin());
		}
		return std::nullopt;
	}

	ConfigImporter::RegionIDList ConfigImporter::GetRegionIDsFromStrings(std::vector<std::string> region_names)
	{
		RegionIDList region_list;

		for (auto& region_name : region_names)
		{
			std::optional<int> micro_id = GetIndexOfStringInStrings(region_name, microscopic_region_names);
			std::optional<int> meso_id = GetIndexOfStringInStrings(region_name, mesoscopic_region_names);

			if (micro_id.has_value())
			{
				region_list.microscopic_ids.emplace_back(micro_id.value());
			}
			else if(meso_id.has_value())
			{
				region_list.mesoscopic_ids.emplace_back(meso_id.value());
			}
			else
			{
				LOG_CRITICAL("The region of name \"{}\" could not be found in list of regions", region_name);
				throw std::exception();
			}
		}
		return region_list;
	}

	ConfigImporter::OptionalShapes ConfigImporter::CreateShape(const Json& shape)
	{
		OptionalShapes shapes;
		std::string type_str = shape["Type"].get<std::string>();
		type_str = SplitShapeName(type_str).shape;
		if (type_str == "Box")
		{
			Vec3d origin = shape["Origin"].get<Vec3d>();
			Vec3d length = shape["Length"].get<Vec3d>();
			shapes.box = std::make_optional<shape::basic::Box>(origin, length);
			shapes.shape = OptionalShapes::Shape::Box;
		}
		else if (type_str == "Sphere")
		{
			Vec3d centre = shape["Centre"].get<Vec3d>();
			double radius = shape["Radius"].get<double>();
			shapes.sphere = std::make_optional<shape::basic::Sphere>(centre, radius);
			shapes.shape = OptionalShapes::Shape::Sphere;
		}
		else if (type_str == "Cylinder")
		{
			Vec3d base_centre = shape["BaseCentre"].get<Vec3d>();
			double radius = shape["Radius"].get<double>();
			double length = shape["Length"].get<double>();
			Axis3D axis = shape["Axis"].get<Axis3D>();
			shapes.cylinder = std::make_optional<shape::basic::Cylinder>(base_centre, radius, length, axis);
			shapes.shape = OptionalShapes::Shape::Cylinder;
		}
		else if (type_str == "RectSurface")
		{
			Vec3d origin = shape["Origin"].get<Vec3d>();
			Vec3d length = shape["Length"].get<Vec3d>();
			shapes.rect_surface = std::make_optional<shape::basic::RectSurface>(origin, length);
			shapes.shape = OptionalShapes::Shape::RectSurface;
		}
		else if (type_str == "CircleSurface")
		{
			Vec3d centre = shape["Centre"].get<Vec3d>();
			double radius = shape["Radius"].get<double>();
			Axis3D axis = shape["Axis"].get<Axis3D>();
			shapes.circle_surface = std::make_optional<shape::basic::CircleSurface>(centre, radius, axis);
			shapes.shape = OptionalShapes::Shape::CircleSurface;
		}
		else if (type_str == "Point")
		{
			Vec3d origin = shape["Origin"].get<Vec3d>();
			shapes.point = std::make_optional<Vec3d>(origin);
			shapes.shape = OptionalShapes::Shape::Point;
		}
		else
		{
			LOG_CRITICAL("Shape must be of type \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", type_str);
			throw std::exception();
		}
		return shapes;
	}



	ConfigImporter::SurfaceShape::SurfaceShape(bool is_surface, const std::string& shape)
		: is_surface(is_surface), shape(shape)
	{

	}

	ConfigImporter::SurfaceShape ConfigImporter::SplitShapeName(const std::string& shape)
	{
		bool is_surface_actor = false;
		std::string non_surface_shape = shape;
		size_t pos = shape.find("Surface");
		if (pos != std::string::npos)
		{
			non_surface_shape = shape.substr(0, pos);
			if (non_surface_shape == "Box" || non_surface_shape == "Sphere" || non_surface_shape == "Cylinder")
			{
				return { true, non_surface_shape };
			}
		}
		return { false, shape };
	}



	void ConfigImporter::CreateEnvironment()
	{
		size_t n_passive_actors;
		if (j.contains("ObserveEachRegion"))
		{
			n_passive_actors = j["MicroscopicRegions"].size() + j["MesoscopicRegions"].size();
		}
		else
		{
			n_passive_actors = j["PassiveActors"].size();
		}

		Environment::Init(j["SaveToFolder"], j["NumberOfRealisations"], j["FinalSimulationTime"], j["NumberOfMoleculeTypes"], j["MicroscopicRegions"].size(), j["MesoscopicRegions"].size(), n_passive_actors, j["ActiveActors"].size(), j["MicroscopicSurfaces"].size(), j["RandomNumberSeed"].get<uint64_t>());

		LOG_INFO("Building Environment");
		LOG_INFO("Microscopic Regions");
		CreateMicroscopicRegions();

		LOG_INFO("Microscopic Surfaces");
		CreateMicroscopicSurfaces();

		LOG_INFO("Mesoscopic Regions");
		CreateMesoscopicRegion();

		LOG_INFO("Passive Actors");
		CreatePassiveActors();

		LOG_INFO("Active Actors");
		CreateActiveActors();

		LOG_INFO("Relationships");
		CreateRelationships();

		LOG_INFO("Reactions");
		CreateReactions();
	}

	void ConfigImporter::CreateMicroscopicRegions()
	{
		for (auto& region : j["MicroscopicRegions"])
		{
			std::vector<microscopic::SurfaceType> surface_types = region["SurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();
			std::vector<double> diffision_coefficients = region["DiffusionCoefficients"].get<std::vector<double>>();
			Vec3i n_subvolumes = region["NumberOfSubvolumes"].get<Vec3i>();
			double time_step = region["TimeStep"].get<double>();
			int priority = region["Priority"].get<int>();

			OptionalShapes shapes = CreateShape(region["Shape"]);
			switch (shapes.shape)
			{
			case OptionalShapes::Shape::Box:
				Environment::AddRegion(shapes.box.value(), surface_types, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			case OptionalShapes::Shape::Sphere:
				Environment::AddRegion(shapes.sphere.value(), surface_types, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			case OptionalShapes::Shape::Cylinder:
				Environment::AddRegion(shapes.cylinder.value(), surface_types, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			}
		}
	}

	void ConfigImporter::CreateMicroscopicSurfaces()
	{
		for (auto& surface : j["MicroscopicSurfaces"])
		{
			std::vector<microscopic::SurfaceType> surface_types = surface["SurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();
			std::vector<std::string> regions_to_act_in = surface["AddToRegions"].get<std::vector<std::string>>();
			bool is_on_region_surface = surface["IsOnRegionSurface"].get<bool>();
			RegionIDList region_list = GetRegionIDsFromStrings(regions_to_act_in);

			microscopic::HighPriorityRelative::SurfaceDirection surface_direction = surface["SurfaceDirection"].get<microscopic::HighPriorityRelative::SurfaceDirection>();

			std::unique_ptr<microscopic::SurfaceShape> surface_shape;
			OptionalShapes shapes = CreateShape(surface["Shape"]);
			
			switch (shapes.shape)
			{
			case OptionalShapes::Shape::Box:
				surface_shape = std::make_unique<microscopic::BoxSurfaceShape>(shapes.box.value());
				break;
			case OptionalShapes::Shape::Sphere:
				surface_shape = std::make_unique<microscopic::SphereSurfaceShape>(shapes.sphere.value());
				break;
			case OptionalShapes::Shape::Cylinder:
				surface_shape = std::make_unique<microscopic::CylinderSurfaceShape>(shapes.cylinder.value());
				break;
			case OptionalShapes::Shape::RectSurface:
				surface_shape = std::make_unique<microscopic::RectSurfaceShape>(shapes.rect_surface.value());
				break;
			case OptionalShapes::Shape::CircleSurface:
				surface_shape = std::make_unique<microscopic::CircleSurfaceShape>(shapes.circle_surface.value());
				break;
			}
			microscopic::Surface surface(std::move(surface_shape), surface_direction);
			Environment::AddSurfaceToMicroscopicRegions(surface, surface_types, is_on_region_surface, region_list.microscopic_ids);
		}
	}

	void ConfigImporter::CreateMesoscopicRegion()
	{
		for (auto& region : j["MesoscopicRegions"])
		{
			Vec3d origin = region["Origin"].get<Vec3d>();
			double subvolume_length = region["SubvolumeLength"].get<double>();
			std::vector<double> diffision_coefficients = region["DiffusionCoefficients"].get<std::vector<double>>();
			Vec3i n_subvolumes = region["NumberOfSubvolumes"].get<Vec3i>();
			int priority = region["Priority"].get<int>();

			Environment::AddMesoscopicRegion(origin, subvolume_length, n_subvolumes, diffision_coefficients, priority);
		}
	}

	void ConfigImporter::CreatePassiveActors()
	{
		if (j.contains("ObserveEachRegion") && j["ObserveEachRegion"].get<bool>())
		{
			Json actor = j["PassiveActors"];
			double start_time = actor["StartTime"].get<double>();
			int priority = actor["Priority"].get<int>();
			double time_step = actor["TimeStep"].get<double>();
			bool record_positions = actor["RecordPositions"].get<bool>();
			bool record_observation_time = actor["RecordObservationTime"].get<bool>();
			MoleculeIDs molecule_types_to_observe;
			molecule_types_to_observe.reserve(n_molecule_types);
			for (int i = 0; i < n_molecule_types; i++)
			{
				molecule_types_to_observe.emplace_back(i);
			}

			for (int i = 0; i < static_cast<int>(Environment::GetRegions().size()); i++)
			{
				Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({ MicroscopicRegionID(i) }), MesoscopicRegionIDs({}),
					molecule_types_to_observe, start_time, priority, time_step, PassiveActorID(static_cast<int>(Environment::GetPassiveActors().size())), record_positions, record_observation_time));
			}

			for (int i = 0; i < static_cast<int>(Environment::GetMesoscopicRegions().size()); i ++)
			{	
				Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(MicroscopicRegionIDs({}), MesoscopicRegionIDs({ MesoscopicRegionID(i) }),
					molecule_types_to_observe, start_time, priority, time_step, PassiveActorID(static_cast<int>(Environment::GetPassiveActors().size())), record_positions, record_observation_time));
			}
		}
		else
		{
			for (auto& actor : j["PassiveActors"])
			{
				double start_time = actor["StartTime"].get<double>();
				int priority = actor["Priority"].get<int>();
				double time_step = actor["TimeStep"].get<double>();

				bool record_positions = actor["RecordPositions"].get<bool>();
				bool record_observation_time = actor["RecordObservationTime"].get<bool>();
				MoleculeIDs molecule_types_to_observe = actor["MoleculeTypesToObserve"].get<MoleculeIDs>();

				MicroscopicRegionIDs microscopic_ids;
				MesoscopicRegionIDs mesoscopic_ids;
				if (actor.contains("RegionsToObserve"))
				{
					std::vector<std::string> regions_to_observe = actor["RegionsToObserve"].get<std::vector<std::string>>();

					RegionIDList region_list = GetRegionIDsFromStrings(regions_to_observe);

					Environment::GetPassiveActors().emplace_back(std::make_unique<ShapelessPassiveActor>(region_list.microscopic_ids, region_list.mesoscopic_ids,
						molecule_types_to_observe, start_time, priority, time_step, PassiveActorID(static_cast<int>(Environment::GetPassiveActors().size())), record_positions, record_observation_time));
				}
				else if (actor.contains("Shape"))
				{
					OptionalShapes shapes = CreateShape(actor["Shape"]);
					std::unique_ptr<PassiveActorShape> passive_actor_shape;
					switch (shapes.shape)
					{
					case OptionalShapes::Shape::Box:
						passive_actor_shape = std::make_unique<PassiveActorBoxShape>(shapes.box.value());
						break;
					case OptionalShapes::Shape::Sphere:
						passive_actor_shape = std::make_unique<PassiveActorSphereShape>(shapes.sphere.value());
						break;
					case OptionalShapes::Shape::Cylinder:
						passive_actor_shape = std::make_unique<PassiveActorCylinderShape>(shapes.cylinder.value());
						break;
					}
					Environment::GetPassiveActors().emplace_back(std::make_unique<ShapedPassiveActor>(std::move(passive_actor_shape), molecule_types_to_observe, start_time, priority, time_step, PassiveActorID(static_cast<int>(Environment::GetPassiveActors().size())), record_positions, record_observation_time));
				}
				else
				{
					LOG_CRITICAL("Passive actor must provide field \"RegionsToObserve\", or \"Shape\" but neither exists");
					throw std::exception();
				}
			}
		}
	}

	void ConfigImporter::CreateActiveActors()
	{
		for (auto& actor : j["ActiveActors"])
		{

			double start_time = actor["StartTime"].get<double>();
			int priority = actor["Priority"].get<int>();

			double action_interval = actor["ActionInterval"].get<double>();
			double release_interval = actor["ReleaseInterval"].get<double>();
			int modulation_strength = actor["ModulationStrength"].get<int>();
			std::vector<int> molecule_types_to_release = actor["MoleculeTypesToRelease"].get<std::vector<int>>();

			std::unique_ptr<ActiveActorShape> active_actor_shape;
			RegionIDList region_list;
			if (actor.contains("Shape"))
			{
				OptionalShapes shapes = CreateShape(actor["Shape"]);
				if (!SplitShapeName(actor["Shape"]["Type"]).is_surface)
				{
					switch (shapes.shape)
					{
					case OptionalShapes::Shape::Box:

						active_actor_shape = std::make_unique<ActiveActorBox>(shapes.box.value());
						break;
					case OptionalShapes::Shape::Sphere:
						active_actor_shape = std::make_unique<ActiveActorSphere>(shapes.sphere.value());
						break;
					case OptionalShapes::Shape::Cylinder:
						active_actor_shape = std::make_unique<ActiveActorCylinder>(shapes.cylinder.value());
						break;
					case OptionalShapes::Shape::RectSurface:
						active_actor_shape = std::make_unique<ActiveActorRectSurface>(shapes.rect_surface.value());
						break;
					case OptionalShapes::Shape::CircleSurface:
						active_actor_shape = std::make_unique<ActiveActorCircleSurface>(shapes.circle_surface.value());
						break;
					case OptionalShapes::Shape::Point:
						active_actor_shape = std::make_unique<ActiveActorPoint>(shapes.point.value());
						break;
					}
				}
				else
				{
					switch (shapes.shape)
					{
					case OptionalShapes::Shape::Box:
						active_actor_shape = std::make_unique<ActiveActorBoxSurface>(shapes.box.value());
						break;
					case OptionalShapes::Shape::Sphere:
						active_actor_shape = std::make_unique<ActiveActorSphereSurface>(shapes.sphere.value());
						break;
					case OptionalShapes::Shape::Cylinder:
						active_actor_shape = std::make_unique<ActiveActorCylinderSurface>(shapes.cylinder.value());
						break;
					}
				}

				if (!actor.contains("RegionsToActIn"))
				{
					for (auto& region : Environment::GetRegions())
					{
						if (active_actor_shape->IsOverlapping(shape::relation::Box(region->GetShape().GetBasicShape().GenerateBoundingBox())))
						{
							region_list.microscopic_ids.emplace_back(region->GetID());
						}
					}

					for (auto& region : Environment::GetMesoscopicRegions())
					{
						if (active_actor_shape->IsOverlapping(shape::relation::Box(region.GetBoundingBox())))
						{
							region_list.mesoscopic_ids.emplace_back(region.GetID());
						}
					}
				}
			}
			
			if (actor.contains("RegionsToActIn"))
			{
				std::vector<std::string> regions_to_act_in = actor["RegionsToActIn"].get<std::vector<std::string>>();
				region_list = GetRegionIDsFromStrings(regions_to_act_in);
				//for (auto& id : region_list.microscopic_ids)
				//{
				//	LOG_INFO("micro id = {}", id);
				//}
				//for (auto& id : region_list.mesoscopic_ids)
				//{
				//	LOG_INFO("meso id = {}", id);
				//}

				if (!actor.contains("Shape"))
				{
					shape::basic::Box bounding_box(Vec3d(0), Vec3d(0));
					if (!region_list.microscopic_ids.empty())
					{
						bounding_box = Environment::GetMicroscopicRegion(region_list.microscopic_ids.front()).GetShape().GetBasicShape().GenerateBoundingBox();
						//LOG_INFO("box = {}", bounding_box);
					}
					else if (!region_list.mesoscopic_ids.empty())
					{
						bounding_box = Environment::GetMesoscopicRegion(region_list.mesoscopic_ids.front()).GetBoundingBox();
						//LOG_INFO("box = {}", bounding_box);
					} // else no regions throw error

					for (auto& region : Environment::GetRegions(region_list.microscopic_ids))
					{
						bounding_box = bounding_box.GenerateBoundingBox(region->GetShape().GetBasicShape().GenerateBoundingBox());
						//LOG_INFO("box = {}", bounding_box);
					}
					for (auto& region : Environment::GetMesoscopicRegions(region_list.mesoscopic_ids))
					{
						bounding_box = bounding_box.GenerateBoundingBox(region->GetBoundingBox());
						//LOG_INFO("box = {}", bounding_box);
					}
					active_actor_shape = std::make_unique<ActiveActorBox>(bounding_box);
					//LOG_INFO("Active actor shape = {}", bounding_box);
				}
			}
			
			std::string type_str = actor["Type"].get<std::string>();
			if (type_str == "RandomTime")
			{
				Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomTime>(action_interval, release_interval,
					molecule_types_to_release, modulation_strength, Environment::GetRegions(region_list.microscopic_ids),
					Environment::GetMesoscopicRegions(region_list.mesoscopic_ids), std::move(active_actor_shape), start_time, priority,
					ActiveActorID(static_cast<int>(Environment::GetActiveActors().size()))));
			}
			else if (type_str == "RandomBits")
			{
				int symbol_size = actor["SymbolSize"].get<int>();
				double slot_interval = actor["SlotInterval"].get<double>();
				double bit_probability = actor["BitProbability"].get<double>();

				Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorRandomBits>(action_interval, release_interval, slot_interval,
					bit_probability, symbol_size, molecule_types_to_release, modulation_strength, Environment::GetRegions(region_list.microscopic_ids),
					Environment::GetMesoscopicRegions(region_list.mesoscopic_ids), std::move(active_actor_shape), start_time, priority,
					ActiveActorID(static_cast<int>(Environment::GetActiveActors().size()))));

			}
			else if (type_str == "NonRandom")
			{
				int symbol_size = actor["SymbolSize"].get<int>();
				double slot_interval = actor["SlotInterval"].get<double>();
				std::vector<int> bit_sequence = actor["BitSequence"].get<std::vector<int>>();

				Environment::GetActiveActors().emplace_back(std::make_unique<ActiveActorNonRandom>(action_interval, release_interval, slot_interval,
					bit_sequence, symbol_size, molecule_types_to_release, modulation_strength, Environment::GetRegions(region_list.microscopic_ids),
					Environment::GetMesoscopicRegions(region_list.mesoscopic_ids), std::move(active_actor_shape), start_time, priority, 
					ActiveActorID(static_cast<int>(Environment::GetActiveActors().size()))));
			}
			else
			{
				LOG_ERROR("The field <{}> expected value of \"RandomTime\", \"RandomBits\" or \"NonRandom\" but was \"{}\"", type_str);
				throw std::exception();
			}
		}
	}

	void ConfigImporter::CreateRelationships()
	{
		for (auto& relationship : j["Relationships"])
		{
			std::string region_a_name = relationship["RegionA"].get<std::string>();
			std::string region_b_name = relationship["RegionB"].get<std::string>();
			Environment::RelationshipPriority priority = relationship["Priority"].get<Environment::RelationshipPriority>();

			RegionIDList region_list = GetRegionIDsFromStrings({ region_a_name , region_b_name });

			if (region_list.mesoscopic_ids.empty())
			{
				// Microscopic Region Relationships
				MicroscopicRegionIDs& ids = region_list.microscopic_ids;
				if (relationship.contains("SurfaceTypes"))
				{
					std::vector<microscopic::SurfaceType> surface_types = relationship["SurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

					Environment::DefineRelationship(ids.at(0), ids.at(1), priority, surface_types);
				}
				else if (relationship.contains("AToBSurfaceTypes") && relationship.contains("BToASurfaceTypes"))
				{
					std::vector<microscopic::SurfaceType> ab_surface_types = relationship["AToBSurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

					std::vector<microscopic::SurfaceType> ba_surface_types = relationship["BToASurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

					Environment::DefineRelationship(ids.at(0), ids.at(1), priority, ab_surface_types, ba_surface_types);
				}
			}
			else if (region_list.microscopic_ids.empty())
			{
				// meso to meso relationship
				MesoscopicRegionIDs& ids = region_list.mesoscopic_ids;
				mesoscopic::Region& region_a = Environment::GetMesoscopicRegion(ids.at(0));
				mesoscopic::Region& region_b = Environment::GetMesoscopicRegion(ids.at(1));
				region_a.AddNeighbour(region_b);
				region_b.AddNeighbour(region_a);
			}
			else
			{
				// hybrid relationship
				microscopic::Region& micro_region = Environment::GetMicroscopicRegion(region_list.microscopic_ids.at(0));
				mesoscopic::Region& meso_region = Environment::GetMesoscopicRegion(region_list.mesoscopic_ids.at(0));

				MoleculeIDs molecule_ids;
				for (int i = 0; i < n_molecule_types; i++)
				{
					molecule_ids.emplace_back(i);
				}
				micro_region.AddNeighbour(meso_region, molecule_ids);

			}

			
			
		}
	}

	void ConfigImporter::CreateReactions()
	{
		LOG_INFO("Zeroth Order Reactions");
		for (auto& reaction : j["ZerothOrderReactions"])
		{
			std::vector<int> products = reaction["Products"].get<std::vector<int>>();
			double reaction_rate = reaction["ReactionRate"].get<double>();
			std::vector<std::string> occur_in_regions = reaction["OccurInRegions"].get<std::vector<std::string>>();
			RegionIDList region_list = GetRegionIDsFromStrings(occur_in_regions);

			ReactionManager::AddZerothOrderReaction(products, reaction_rate, region_list.microscopic_ids, region_list.mesoscopic_ids);
		}
		LOG_INFO("First Order Reactions");
		for (auto& reaction : j["FirstOrderReactions"])
		{
			MoleculeID reactant = reaction["Reactant"].get<MoleculeID>();
			std::vector<int> products = reaction["Products"].get<std::vector<int>>();
			double reaction_rate = reaction["ReactionRate"].get<double>();
			std::vector<std::string> occur_in_regions = reaction["OccurInRegions"].get<std::vector<std::string>>();
			RegionIDList region_list = GetRegionIDsFromStrings(occur_in_regions);

			ReactionManager::AddFirstOrderReaction(reactant, products, reaction_rate, region_list.microscopic_ids, region_list.mesoscopic_ids);
		}
		LOG_INFO("Second Order Reactions");
		for (auto& reaction : j["SecondOrderReactions"])
		{
			MoleculeID reactant_a = reaction["ReactantA"].get<MoleculeID>();
			MoleculeID reactant_b = reaction["ReactantB"].get<MoleculeID>();
			std::vector<int> products = reaction["Products"].get<std::vector<int>>();
			int reaction_rate = reaction["ReactionRate"].get<int>();
			double binding_radius = reaction["BindingRadius"].get<double>();
			//LOG_INFO("binding radius = {}", binding_radius);
			double unbinding_radius = reaction["UnBindingRadius"].get<double>();
			std::vector<std::string> occur_in_regions = reaction["OccurInRegions"].get<std::vector<std::string>>();
			RegionIDList region_list = GetRegionIDsFromStrings(occur_in_regions);

			ReactionManager::AddSecondOrderReaction(reactant_a, reactant_b, products, binding_radius, unbinding_radius, reaction_rate, region_list.microscopic_ids, region_list.mesoscopic_ids);
		}
	}

	ConfigImporter::OptionalShapes::OptionalShapes()
		: shape(Shape::None)
	{
	}
}