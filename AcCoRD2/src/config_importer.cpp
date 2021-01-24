#include "pch.h"
#include "config_importer.h"
#include "json_key_pair.h"
#include "environment.h"
#include <fstream>
// construction classes
#include "basic_cylinder.h"
#include "basic_sphere.h"
#include "shapeless_passive_actor.h"
#include "box_passive_actor.h"
#include "microscopic_region.h"
#include "environment.h"
#include "event_queue.h"
#include "event.h"
#include "passive_actor.h"
#include "shapeless_passive_actor.h"
#include "box_passive_actor.h"
#include "microscopic_box_surface_shape.h"
#include "microscopic_surface_shape.h"
#include "microscopic_sphere_surface_shape.h"
#include "microscopic_cylinder_surface_shape.h"
#include "collision_cylinder.h"
#include "relation_cylinder.h"
#include "relation_sphere.h"
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


namespace accord
{
	ConfigImporter::ConfigImporter(std::string file_path)
		: n_molecule_types(0)
	{
		// Check file path is valid
		std::ifstream i(file_path);
		if (!i.is_open())
		{
			LOG_ERROR("Could not open config file <{}>", file_path);
		}
		try
		{
			i >> j;
		}
		catch (Json::parse_error& e)
		{
			LOG_ERROR("Message: {} \nException id: {}\nByte position of error: {}", e.what(), e.id, e.byte);
			throw std::exception();
		}

		ValidateJson();
		CreateEnvironment();
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

		ValidateMicroscopicRegions(config);
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
		else
		{
			LOG_ERROR("The field <{}> expected value of \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", shape_type.Log(), type_str);
			throw std::exception();
		}
	}

	size_t ConfigImporter::ValidateMicroscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MicroscopicRegions"))
		{
			JsonKeyPair microscopic_regions = config.Add("MicroscopicRegions").IsArray();
			size_t n = microscopic_regions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				microscopic_regions.SetIndex(i);

				JsonKeyPair name = microscopic_regions.Add("Name").IsString();
				region_names.emplace_back(name.GetJson().get<std::string>());
				microscopic_region_names.emplace_back(name.GetJson().get<std::string>());

				microscopic_regions.Add("SurfaceType").IsString();
				microscopic_regions.Add("DiffusionCoefficients").IsArrayOfNumbers().HasSize(n_molecule_types);
				JsonKeyPair number_of_subvolumes = microscopic_regions.Add("NumberOfSubvolumes").IsArrayOfArrays().HasSize(n_molecule_types);

				for (size_t i2 = 0; i2 < n_molecule_types; i2++)
				{
					number_of_subvolumes.SetIndex(i2);
					JsonKeyPair nos(number_of_subvolumes.GetJson());
					nos.IsArrayOfInts().HasSize(3);
				}

				microscopic_regions.Add("TimeStep").IsNumber().IsPositive();
				microscopic_regions.Add("Priority").IsInt();

				JsonKeyPair shape_object = microscopic_regions.Add("Shape").IsObject();
				ValidateShape(shape_object);
			}
			return n;
		}
		return 0;
	}

	size_t ConfigImporter::ValidateMesoscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MesoscopicRegions"))
		{
			JsonKeyPair mesoscopic_regions = config.Add("MesoscopicRegions").IsArray();
			size_t n = mesoscopic_regions.GetArraySize();

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
			return n;
		}
		return 0;
	}

	size_t ConfigImporter::ValidateActiveActors(JsonKeyPair& config)
	{
		if (config.IsKey("ActiveActors"))
		{
			JsonKeyPair active_actors = config.Add("ActiveActors");
			active_actors.IsArray();
			size_t n = active_actors.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				active_actors.SetIndex(i);

				active_actors.Add("Name").IsString();
				active_actors.Add("StartTime").IsNumber().IsNonNegative();
				active_actors.Add("Priority").IsInt();
				active_actors.Add("ActionInterval").IsNumber().IsPositive();
				active_actors.Add("ReleaseInterval").IsNumber().IsPositive();
				active_actors.Add("ModulationStrength").IsInt().IsPositive();
				active_actors.Add("MoleculeTypesToRelease").IsArrayOfInts().IsInRange(0, max_molecule_id);
				active_actors.Add("RegionsToActIn").IsArrayOfStrings().IsEachOneOf(region_names);

				JsonKeyPair shape_object = active_actors.Add("Shape").IsObject();
				ValidateShape(shape_object);

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
					active_actors.Add("BitSequence").IsInt().IsInRange(0, 1);
				}
				else
				{
					LOG_ERROR("The field <{}> expected value of \"RandomTime\", \"RandomBits\" or \"NonRandom\" but was \"{}\"", type.Log(), type_str);
					throw std::exception();
				}
			}
			return n;
		}
		return 0;
	}

	size_t ConfigImporter::ValidatePassiveActors(JsonKeyPair& config)
	{
		if (config.IsKey("PassiveActors"))
		{
			JsonKeyPair passive_actors = config.Add("PassiveActors");
			passive_actors.IsArray();
			size_t n = passive_actors.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				passive_actors.SetIndex(i);

				passive_actors.Add("Name").IsString();
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
			return 0;
		}
		return 0;
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

				relationships.Add("RegionA").IsString().IsOneOf(microscopic_region_names);
				relationships.Add("RegionB").IsString().IsOneOf(microscopic_region_names);;
				relationships.Add("Priority").IsString().IsOneOf<std::string>({"A", "B", "None"});;	

				std::vector<std::string> surface_types = { "Absorbing", "Adsorbing", "Membrane", "Reflecting", "None" };
				
				if (relationships.IsKey("SurfaceTypes"))
				{
					relationships.Add("SurfaceTypes").IsArrayOfStrings().IsEachOneOf(surface_types);
				} else if (relationships.IsKey("AToBSurfaceTypes") && relationships.IsKey("BToASurfaceTypes"))
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

	void ConfigImporter::ValidateZerothOrderReactions(JsonKeyPair& config)
	{
		if (config.IsKey("ZerothOrderReactions"))
		{
			JsonKeyPair reactions = config.Add("ZerothOrderReactions").IsArray();
			size_t n = reactions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				reactions.SetIndex(i);

				reactions.Add("Products").IsArrayOfInts().IsInRange(0, max_molecule_id);
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
				reactions.Add("Products").IsArrayOfInts().IsInRange(0, max_molecule_id);
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
				reactions.Add("Products").IsArrayOfInts().IsInRange(0, max_molecule_id);
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
		else
		{
			LOG_CRITICAL("Shape must be of type \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", type_str);
			throw std::exception();
		}
		return shapes;
	}



	void ConfigImporter::CreateEnvironment()
	{
		Environment::Init(j["SaveToFolder"], j["NumberOfRealisations"], j["FinalSimulationTime"], j["NumberOfMoleculeTypes"], j["MicroscopicRegions"].size(), j["MesoscopicRegions"].size(), j["PassiveActors"].size(), j["ActiveActors"].size(), j["RandomNumberSeed"].get<uint64_t>());

		LOG_INFO("Importing Microscopic Regions");
		CreateMicroscopicRegions();

		LOG_INFO("Importing Mesoscopic Regions");
		CreateMesoscopicRegion();

		LOG_INFO("Importing PassiveActors");
		CreatePassiveActors();

		LOG_INFO("Importing ActiveActors");
		CreateActiveActors();

		LOG_INFO("Importing Relationships");
		CreateRelationships();

		LOG_INFO("Importing Reactions");
		CreateReactions();
	}

	void ConfigImporter::CreateMicroscopicRegions()
	{
		for (auto& region : j["MicroscopicRegions"])
		{
			microscopic::SurfaceType surface_type = region["SurfaceType"].get<microscopic::SurfaceType>();
			std::vector<double> diffision_coefficients = region["DiffusionCoefficients"].get<std::vector<double>>();
			std::vector<Vec3i> n_subvolumes = region["NumberOfSubvolumes"].get<std::vector<Vec3i>>();
			double time_step = region["TimeStep"].get<double>();
			int priority = region["Priority"].get<int>();

			OptionalShapes shapes = CreateShape(region["Shape"]);
			switch (shapes.shape)
			{
			case OptionalShapes::Shape::Box:
				Environment::AddRegion(shapes.box.value(), surface_type, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			case OptionalShapes::Shape::Sphere:
				Environment::AddRegion(shapes.sphere.value(), surface_type, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			case OptionalShapes::Shape::Cylinder:
				Environment::AddRegion(shapes.cylinder.value(), surface_type, diffision_coefficients, n_subvolumes, time_step, priority);
				break;
			}
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
				switch (shapes.shape)
				{
				case OptionalShapes::Shape::Box:
					Environment::GetPassiveActors().emplace_back(std::make_unique<BoxPassiveActor>(shapes.box.value(), molecule_types_to_observe, start_time, priority, time_step, PassiveActorID(static_cast<int>(Environment::GetPassiveActors().size())), record_positions, record_observation_time));
					break;
				case OptionalShapes::Shape::Sphere:
					break;
				case OptionalShapes::Shape::Cylinder:
					break;
				}
			}
			else
			{
				LOG_CRITICAL("Passive actor must provide field \"RegionsToObserve\", or \"Shape\" but neither exists");
				throw std::exception();
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
			MoleculeIDs molecule_types_to_observe = actor["MoleculeTypesToRelease"].get<MoleculeIDs>();

			std::vector<std::string> regions_to_act_in = actor["RegionsToActIn"].get<std::vector<std::string>>();
			RegionIDList region_list = GetRegionIDsFromStrings(regions_to_act_in);

			OptionalShapes shapes = CreateShape(actor["Shape"]);
			std::unique_ptr<ActiveActorShape> active_actor_shape;
			switch (shapes.shape)
			{
			case OptionalShapes::Shape::Box:
				active_actor_shape = std::make_unique<ActiveActorBox>(shapes.box.value());
				break;
			case OptionalShapes::Shape::Sphere:
				break;
			case OptionalShapes::Shape::Cylinder:
				break;
			}

			std::string type_str = actor["Type"].get<std::string>();
			if (type_str == "RandomTime")
			{
			}
			else if (type_str == "RandomBits")
			{
				int symbol_size = actor["SymbolSize"].get<int>();
				double slot_interval = actor["SlotInterval"].get<double>();
				double bit_probability = actor["BitProbability"].get<double>();
			}
			else if (type_str == "NonRandom")
			{
				int symbol_size = actor["SymbolSize"].get<int>();
				double slot_interval = actor["SlotInterval"].get<double>();
				std::vector<int> bit_sequence = actor["BitSequence"].get<std::vector<int>>();
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

			std::optional<MicroscopicRegionID> region_a = GetIndexOfStringInStrings(region_a_name, microscopic_region_names);
			if (!region_a.has_value())
			{
				LOG_ERROR("Region a {} could not be found in list of regions", region_a_name);
				throw std::exception();
			}

			std::optional<MicroscopicRegionID> region_b = GetIndexOfStringInStrings(region_b_name, microscopic_region_names);
			if (!region_b.has_value())
			{
				LOG_ERROR("Region b {} could not be found in list of regions", region_b_name);
				throw std::exception();
			}

			if (relationship.contains("SurfaceTypes"))
			{
				std::vector<microscopic::SurfaceType> surface_types = relationship["SurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

				Environment::DefineRelationship(*region_a, *region_b, priority, surface_types);
			}
			else if (relationship.contains("AToBSurfaceTypes") && relationship.contains("BToASurfaceTypes"))
			{
				std::vector<microscopic::SurfaceType> ab_surface_types = relationship["AToBSurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

				std::vector<microscopic::SurfaceType> ba_surface_types = relationship["BToASurfaceTypes"].get<std::vector<microscopic::SurfaceType>>();

				Environment::DefineRelationship(*region_a, *region_b, priority, ab_surface_types, ba_surface_types);
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
			MoleculeID reactant_b = reaction["ReactantA"].get<MoleculeID>();
			std::vector<int> products = reaction["Products"].get<std::vector<int>>();
			int reaction_rate = reaction["ReactionRate"].get<int>();
			double binding_radius = reaction["BindingRadius"].get<double>();
			double unbinding_radius = reaction["UnBindingRadius"].get<double>();
			std::vector<std::string> occur_in_regions = reaction["OccurInRegions"].get<std::vector<std::string>>();
			RegionIDList region_list = GetRegionIDsFromStrings(occur_in_regions);

			ReactionManager::AddSecondOrderReaction(reactant_a, reactant_b, products, reaction_rate, binding_radius, unbinding_radius, region_list.microscopic_ids, region_list.mesoscopic_ids);
		}
	}
}