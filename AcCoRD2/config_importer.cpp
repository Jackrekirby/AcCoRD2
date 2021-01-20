#include "pch.h"
#include "config_importer.h"
#include "json_key_pair.h"
#include <fstream>

namespace accord
{
	ConfigImporter::ConfigImporter(std::string file_path)
	{
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
	}

	void ConfigImporter::ValidateJson()
	{
		JsonKeyPair config(j);
		JsonKeyPair a;

		a = config.Add("NumberOfRepeats");
		a.IsInt();
		a.IsPositive();
		a = config.Add("FinalSimulationTime");
		a.IsNumber();
		a.IsPositive();
		a = config.Add("RandomNumberSeed");
		a.IsInt();
		a.IsPositive();
		config.Add("NumberOfMoleculeTypes");
		a.IsInt();
		a.IsPositive();

		ValidateMicroscopicRegions(config);
		ValidateMesoscopicRegions(config);
		ValidateActiveActors(config);
		ValidatePassiveActors(config);
		// reactions
		// neighbour relationships
	}

	void ConfigImporter::ValidateShape(JsonKeyPair& shape_owner)
	{
		JsonKeyPair shape = shape_owner.Add("Shape");
		shape.IsString();
		std::string shape_str = shape.GetJson().get<std::string>();
		if (shape_str == "Box")
		{
			shape_owner.Add("Origin").IsArrayOfNumbers();
			JsonKeyPair length = shape_owner.Add("Length");
			length.IsArrayOfNumbers();
			length.IsGreaterThan(0);
		}
		else if (shape_str == "Sphere")
		{
			shape_owner.Add("Centre").IsArrayOfNumbers();
			shape_owner.Add("Radius").IsArrayOfNumbers();
		}
		else if (shape_str == "Cylinder")
		{
			shape_owner.Add("Origin").IsArrayOfNumbers();
			shape_owner.Add("Length").IsArrayOfNumbers();
			shape_owner.Add("Axis").IsArrayOfNumbers();
		}
		else
		{
			LOG_ERROR("The field <{}> expected value of \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", shape.Log(), shape_str);
			throw std::exception();
		}
	}

	size_t ConfigImporter::ValidateMicroscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MicroscopicRegions"))
		{
			JsonKeyPair microscopic_regions = config.Add("MicroscopicRegions");
			microscopic_regions.IsStructure();
			size_t n = microscopic_regions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				microscopic_regions.SetIndex(i);
				JsonKeyPair name = microscopic_regions.Add("Name");
				name.IsString();
				region_names.emplace_back(name.GetJson().get<std::string>());
				microscopic_regions.Add("SurfaceType").IsString();
				microscopic_regions.Add("DiffusionCoefficients").IsArrayOfNumbers();
				microscopic_regions.Add("NumberOfSubvolumes").IsArrayOfInts();
				microscopic_regions.Add("TimeStep").IsNumber();
				microscopic_regions.Add("Priority").IsInt();

				ValidateShape(microscopic_regions);
			}
			return n;
		}
		return 0;
	}

	size_t ConfigImporter::ValidateMesoscopicRegions(JsonKeyPair& config)
	{
		if (config.IsKey("MesoscopicRegions"))
		{
			JsonKeyPair mesoscopic_regions = config.Add("MesoscopicRegions");
			mesoscopic_regions.IsStructure();
			size_t n = mesoscopic_regions.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				mesoscopic_regions.SetIndex(i);
				JsonKeyPair name = mesoscopic_regions.Add("Name");
				name.IsString();
				region_names.emplace_back(name.GetJson().get<std::string>());
				mesoscopic_regions.Add("Origin").IsArrayOfNumbers();
				mesoscopic_regions.Add("SubvolumeLength").IsArrayOfNumbers();
				mesoscopic_regions.Add("NumberOfSubvolumes").IsArrayOfInts();
				mesoscopic_regions.Add("DiffusionCoefficients").IsArrayOfNumbers();
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
			active_actors.IsStructure();
			size_t n = active_actors.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				active_actors.SetIndex(i);

				active_actors.Add("Name").IsString();
				active_actors.Add("StartTime").IsNumber();
				active_actors.Add("Priority").IsInt();

				active_actors.Add("ActionInterval").IsNumber();
				active_actors.Add("ReleaseInterval").IsNumber();
				active_actors.Add("ModulationStrength").IsInt();
				active_actors.Add("MoleculeTypesToRelease").IsArrayOfInts();

				JsonKeyPair region_to_act_in = active_actors.Add("RegionsToActIn");
				region_to_act_in.IsArrayOfStrings();
				region_to_act_in.IsEachOneOf(region_names);

				ValidateShape(active_actors);

				JsonKeyPair type = active_actors.Add("Type");
				type.IsString();
				std::string type_str = type.GetJson().get<std::string>();
				if (type_str == "RandomTime")
				{
				}
				else if (type_str == "RandomBits")
				{
					active_actors.Add("SymbolSize").IsInt();
					active_actors.Add("SlotInterval").IsNumber();
					active_actors.Add("BitProbability").IsNumber();
				}
				else if (type_str == "NonRandom")
				{
					active_actors.Add("SymbolSize").IsInt();
					active_actors.Add("SlotInterval").IsNumber();
					active_actors.Add("BitSequence").IsInt();
				}
				else
				{
					LOG_ERROR("The field <{}> expected value of \"Box\", \"Sphere\" or \"Cylinder\" but was \"{}\"", type.Log(), type_str);
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
			passive_actors.IsStructure();
			size_t n = passive_actors.GetArraySize();

			for (size_t i = 0; i < n; i++)
			{
				passive_actors.SetIndex(i);

				passive_actors.Add("Name").IsString();
				passive_actors.Add("StartTime").IsNumber();
				passive_actors.Add("Priority").IsInt();
				passive_actors.Add("TimeStep").IsNumber();

				passive_actors.Add("RecordPositions").IsBool();
				passive_actors.Add("RecordObservationTime").IsBool();
				passive_actors.Add("MoleculeTypesToObserve").IsArrayOfInts();

				if (passive_actors.IsKey("RegionsToObserve"))
				{
					JsonKeyPair region_to_observe = passive_actors.Add("RegionsToObserve");
					region_to_observe.IsArrayOfStrings();
					region_to_observe.IsEachOneOf(region_names);
				}
				else if (passive_actors.IsKey("Shape"))
				{
					ValidateShape(passive_actors);
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
}