#pragma once
#include "pch.h"
#include <fstream>
#include <sstream>

namespace accord
{
	class JsonKeyPair
	{
	public:
		//JsonKeyPair(const Json& j, const std::string& key)
		//	: j(j), keys(key), index(0), has_index(false)
		//{

		//}

		JsonKeyPair(const Json& j)
			: j(j), keys(""), index(0), has_index(false)
		{

		}

		JsonKeyPair(const JsonKeyPair& json_key_pair, const std::string& key)
			: j(json_key_pair.GetJson()[key]), keys(json_key_pair.keys), index(0), has_index(false)
		{
			if (json_key_pair.has_index)
			{
				keys.append(fmt::format("[{}]", json_key_pair.index));
			}

			if (!keys.empty())
			{
				keys.append("::");
			}
			
			keys.append(key);
		}

		void DoesExist(const std::string& key) const 
		{
			if (!j.contains(key))
			{
				LOG_ERROR("The key <{}> could not be found", Log(key));
				throw std::exception();
			}
		}

		JsonKeyPair Add(const std::string& key) const
		{
			DoesExist(key);
			return JsonKeyPair((*this), key);
		}

		void SetIndex(size_t index)
		{
			this->index = index;
			has_index = true;
		}

		std::string Log(const std::string& key) const
		{
			if (!keys.empty())
			{
				if (has_index)
				{
					return fmt::format("{}[{}]::{}", keys, index, key);
				}
				else
				{
					return fmt::format("{}::{}", keys, key);
				}
			}
			else
			{
				return key;
			}
		}

		std::string Log() const
		{
			if (!keys.empty())
			{
				if (has_index)
				{
					return fmt::format("{}[{}]", keys, index);
				}
				else
				{
					return fmt::format("{}", keys);
				}
			}
			else
			{
				LOG_ERROR("Attempting to Log a Json Key but not key provided");
				throw std::exception();
			}
		}

		const std::string& GetKeys() const
		{
			return keys;
		}

		const Json& GetJson() const
		{
			if (has_index)
			{
				if (j.is_array())
				{
					return j.at(index);
				}
			}
			return j;
		}



		void ThrowIncorrectType(const std::string& type)
		{
			std::string keys;
			LOG_ERROR("<{}> expected {} but was type {}", Log(), type, std::string(j.type_name()));

			throw std::exception();
		}

		

		void IsBool()
		{
			if (!j.is_boolean())
			{
				ThrowIncorrectType("boolean");
			}
		}

		void IsInt()
		{
			if (!j.is_number_integer())
			{
				ThrowIncorrectType("integer");
			}
		}

		void IsFloat()
		{
			if (!j.is_number_float())
			{
				ThrowIncorrectType("float");
			}
		}

		void IsNumber()
		{
			if (!j.is_number())
			{
				ThrowIncorrectType("float or int");
			}
		}

		void IsString()
		{
			if (!j.is_string())
			{
				ThrowIncorrectType("string");
			}
		}

		void IsArray()
		{
			if (!j.is_array())
			{
				ThrowIncorrectType("array");
			}
		}

		void IsObject()
		{
			if (!j.is_object())
			{
				ThrowIncorrectType("object");
			}
		}

		void IsArrayOrObject()
		{
			if (!j.is_structured())
			{
				ThrowIncorrectType("array or object");
			}
		}
	private:
		Json j;
		std::string keys;
		size_t index;
		bool has_index;
	};

	class ConfigImporter
	{
	public:
		ConfigImporter(std::string file_path)
		{
			std::ifstream i(file_path);
			i >> j;

			if (j["MicroscopicRegions"]["Origin"][0].is_number())
			{
				LOG_INFO("is number!");
			}

			JsonKeyPair k(j);
			k.Add("NumberOfRepeats").IsBool();
			IsBool(k, "NumberOfRepeats");
			IsNumber(k, "FinalSimulationTime");
			IsInt(k, "RandomNumberSeed");
			IsInt(k, "NumberOfMoleculeTypes");

			IsArrayOrObject(k, "MicroscopicRegions");
			JsonKeyPair microscopic_region(k, "MicroscopicRegions");
			size_t n = GetArraySize(microscopic_region.GetJson());
			
			for (size_t i = 0; i < n; i++)
			{
				microscopic_region.SetIndex(i);

				if (microscopic_region.GetJson()["Origin"][0].is_number())
				{
					LOG_INFO("is also number!");
				}
				

				IsString(microscopic_region,	"Name");
				IsString(microscopic_region,	"SurfaceType");
				IsArray(microscopic_region,		"DiffusionCoefficients");
				IsArray(microscopic_region,		"NumberOfSubvolumes");
				IsNumber(microscopic_region,	"TimeStep");
				IsInt(microscopic_region,		"Priority");

				IsString(microscopic_region,	"Shape");
				std::string shape_type = microscopic_region.GetJson()["Shape"].get<std::string>();
				if (shape_type == "Box")
				{
					IsTypeArray(microscopic_region, "Origin", &ConfigImporter::IsNumbers);
					IsTypeArray(microscopic_region, "Length", &ConfigImporter::IsInt);
				} else if (shape_type == "Sphere")
				{
					//IsArray(microscopic_region, "Centre");
					//IsNumber(microscopic_region, "Radius");
				} else if (shape_type == "Cylinder")
				{
					//IsArray(microscopic_region, "Origin");
					//IsArray(microscopic_region, "Length");
					//IsArray(microscopic_region, "Axis");
				}
			}
			//IsArray(k, "PassiveActors");
			//
			//IsArray(k, "MesoscopicRegions");
		}
	private:
		Json j;

		void ThrowIncorrectType(const std::string& type, const JsonKeyPair& json_key_pair, const std::string& key, const Json& value)
		{
			std::string keys;
			LOG_ERROR("<{}> expected {} but was type {}", json_key_pair.Log(key), type, std::string(value.type_name()));
			
			throw std::exception();
		}

		void ThrowIncorrectType(const std::string& type, const JsonKeyPair& json_key_pair, const Json& value)
		{
			std::string keys;
			LOG_ERROR("<{}> expected {} but was type {}", json_key_pair.Log(), type, std::string(value.type_name()));

			throw std::exception();
		}

		void DoesExist(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			if (!json_key_pair.GetJson().contains(key))
			{
				LOG_ERROR("The key <{}> could not be found", json_key_pair.Log(key));
				throw std::exception();
			}
		}

		size_t GetArraySize(const Json& value)
		{
			if (value.is_array())
			{
				return value.size();
			}
			else if(value.is_object())
			{
				return 1;
			}
			else
			{
				LOG_CRITICAL("Expected array or object but was type {}", std::string(value.type_name()));
				throw std::exception();
			}
		}


		void IsBool(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_boolean())
			{
				ThrowIncorrectType("bool", json_key_pair, value);
			}
		}

		void IsInt(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_number_integer())
			{
				ThrowIncorrectType("integer", json_key_pair, value);
			}
		}

		void IsFloat(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_number_float())
			{
				ThrowIncorrectType("float", json_key_pair, value);
			}
		}

		void IsNumber(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_number())
			{
				ThrowIncorrectType("number", json_key_pair, value);
			}
		}

		void IsString(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_string())
			{
				ThrowIncorrectType("string", json_key_pair, value);
			}
		}

		void IsArray(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_array())
			{
				ThrowIncorrectType("array", json_key_pair, value);
			}
		}

		void IsObject(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_object())
			{
				ThrowIncorrectType("object", json_key_pair, value);
			}
		}

		void IsArrayOrObject(const JsonKeyPair& json_key_pair)
		{
			Json value = json_key_pair.GetJson();
			if (!value.is_structured())
			{
				ThrowIncorrectType("array or object", json_key_pair, value);
			}
		}


		void IsBool(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsBool(a);
		}

		void IsInt(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsInt(a);
		}

		void IsFloat(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsFloat(a);
		}

		void IsNumber(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsNumber(a);
		}

		void IsString(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsString(a);
		}

		void IsArray(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsArray(a);
		}

		void IsObject(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsObject(a);
		}

		void IsArrayOrObject(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			DoesExist(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			IsArrayOrObject(a);
		}
		

		void IsNumbers(const JsonKeyPair& json_key_pair)
		{
			auto& value = json_key_pair.GetJson();
			if (!value.is_number())
			{
				ThrowIncorrectType("number", json_key_pair, value);
			}
		}

		void IsTypeArray(const JsonKeyPair& json_key_pair, const std::string& key, void(ConfigImporter::*IsType)(const JsonKeyPair&))
		{
			IsArray(json_key_pair, key);
			JsonKeyPair a(json_key_pair, key);
			Json n = json_key_pair.GetJson()[key].size();
			for (size_t i = 0; i < n; i++)
			{
				a.SetIndex(i);
				(this->*IsType)(a);
			}
		}

		void IsIntArray(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			IsTypeArray(json_key_pair, key, &ConfigImporter::IsInt);
		}

		void IsNumberArray(const JsonKeyPair& json_key_pair, const std::string& key)
		{
			IsTypeArray(json_key_pair, key, &ConfigImporter::IsNumber);
		}


	};
}