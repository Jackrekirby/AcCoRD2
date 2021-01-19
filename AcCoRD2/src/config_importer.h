#pragma once
#include "pch.h"
#include <fstream>
#include <sstream>

namespace accord
{
	class JsonKeyPair
	{
	public:
		JsonKeyPair(const Json& j, const std::string& key)
			: j(j), keys(key)
		{

		}

		JsonKeyPair(const Json& j)
			: j(j), keys("")
		{

		}

		JsonKeyPair(const JsonKeyPair& json_key_pair, const std::string& key)
			: j(json_key_pair.j[key]), keys(json_key_pair.keys)
		{
			if (!keys.empty())
			{
				this->keys.append("::");
			}
			this->keys.append(key);
		}

		const std::string& GetKeys() const
		{
			return keys;
		}

		const Json& GetJson() const
		{
			return j;
		}
	private:
		Json j;
		std::string keys;
	};

	class ConfigImporter
	{
	public:
		ConfigImporter(std::string file_path)
		{
			std::ifstream i(file_path);
			i >> j;
			JsonKeyPair k(j);
			IsInt(k, "NumberOfRepeats");
			IsNumber(k, "FinalSimulationTime");
			IsInt(k, "RandomNumberSeed");
			IsInt(k, "NumberOfMoleculeTypes");

			IsArray(k, "MicroscopicRegions");
			JsonKeyPair microscopic_region(k, "MicroscopicRegions");
			size_t n = microscopic_region.GetJson().size();

			for (size_t i = 0; i < n; i++)
			{
				IsString(microscopic_region,	"Name");
				IsString(microscopic_region,	"SurfaceType");
				IsArray(microscopic_region,		"DiffusionCoefficients");
				IsArray(microscopic_region,		"NumberOfSubvolumes");
				IsNumber(microscopic_region,	"TimeStep");
				IsInt(microscopic_region,		"Priority");

				IsString(microscopic_region, "Shape");
				JsonKeyPair shape(microscopic_region, "Shape");
				std::string shape_type = shape.GetJson()["Shape"].get<std::string>();

				if (shape_type == "Box")
				{

				} else if (shape_type == "Sphere")
				{

				} else if (shape_type == "Cylinder")
				{

				}
			}
			IsArray(k, "PassiveActors");
			
			IsArray(k, "MesoscopicRegions");
		}
	private:
		Json j;

		void AddKey(std::string& keys, const std::string& key)
		{
			keys.append(" ");
			keys.append(key);
		}

		Json GetValue(const std::string& keys)
		{
			std::istringstream ss(keys);
			std::string key;
			Json k = j;
			while (ss >> key)
			{
				k = k[key];
			}
			return k;
		}

		void ThrowIncorrectType(const std::string& type, const JsonKeyPair& json_key_pair, const std::string& key, const Json& value)
		{
			if (json_key_pair.GetKeys().empty())
			{
				LOG_ERROR("<{}> expected {} but was type {}", key, type, std::string(value.type_name()));
			}
			else
			{
				LOG_ERROR("<{}::{}> expected {} but was type {}", json_key_pair.GetKeys(), key, type, std::string(value.type_name()));
			}
			throw std::exception();
		}

		void IsString(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_string())
			{
				ThrowIncorrectType("string", json_key_pair, key, value);
			}
		}

		void IsArray(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_array())
			{
				ThrowIncorrectType("array", json_key_pair, key, value);
			}
		}

		void IsObject(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_object())
			{
				ThrowIncorrectType("object", json_key_pair, key, value);
			}
		}

		void IsBool(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_boolean())
			{
				ThrowIncorrectType("bool", json_key_pair, key, value);
			}
		}

		void IsInt(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_string())
			{
				ThrowIncorrectType("integer", json_key_pair, key, value);
			}
		}

		void IsFloat(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_string())
			{
				ThrowIncorrectType("float", json_key_pair, key, value);
			}
		}

		void IsNumber(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			Json value = json_key_pair.GetJson()[key];
			if (!value.is_string())
			{
				ThrowIncorrectType("number", json_key_pair, key, value);
			}
		}
	};
}