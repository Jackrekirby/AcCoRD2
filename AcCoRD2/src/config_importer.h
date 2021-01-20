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
			LOG_ERROR("<{}> expected {} but was type {}", Log(), type, std::string(GetJson().type_name()));

			throw std::exception();
		}

		size_t GetArraySize() const
		{
			if (GetJson().is_array())
			{
				return GetJson().size();
			}
			else if (GetJson().is_object())
			{
				return 1;
			}
			else
			{
				LOG_CRITICAL("Expected array or object but was type {}", std::string(GetJson().type_name()));
				throw std::exception();
			}
		}
		

		void IsBool()
		{
			if (!GetJson().is_boolean())
			{
				ThrowIncorrectType("boolean");
			}
		}

		void IsInt()
		{
			if (!GetJson().is_number_integer())
			{
				ThrowIncorrectType("integer");
			}
		}

		void IsFloat()
		{
			if (!GetJson().is_number_float())
			{
				ThrowIncorrectType("float");
			}
		}

		void IsNumber()
		{
			if (!GetJson().is_number())
			{
				ThrowIncorrectType("float or int");
			}
		}

		void IsString()
		{
			if (!GetJson().is_string())
			{
				ThrowIncorrectType("string");
			}
		}

		void IsArray()
		{
			if (!GetJson().is_array())
			{
				ThrowIncorrectType("array");
			}
		}

		void IsObject()
		{
			if (!GetJson().is_object())
			{
				ThrowIncorrectType("object");
			}
		}

		void IsStructure()
		{
			if (!j.is_structured())
			{
				ThrowIncorrectType("array or object");
			}
		}


		void IsArrayOfType(void(JsonKeyPair::* IsType)())
		{
			IsArray();
			size_t n = GetArraySize();
			for (size_t i = 0; i < n; i++)
			{
				SetIndex(i);
				(this->*IsType)();
			}
		}

		void IsArrayOfBools()
		{
			IsArrayOfType(&JsonKeyPair::IsBool);
		}

		void IsArrayOfInts()
		{
			IsArrayOfType(&JsonKeyPair::IsInt);
		}

		void IsArrayOfFloats()
		{
			IsArrayOfType(&JsonKeyPair::IsFloat);
		}

		void IsArrayOfNumbers()
		{
			IsArrayOfType(&JsonKeyPair::IsNumber);
		}

		void IsArrayOfArrays()
		{
			IsArrayOfType(&JsonKeyPair::IsArray);
		}

		void IsArrayOfObjects()
		{
			IsArrayOfType(&JsonKeyPair::IsObject);
		}

		void IsArrayOfStructures()
		{
			IsArrayOfType(&JsonKeyPair::IsStructure);
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

			JsonKeyPair config(j);
			config.Add("NumberOfRepeats").IsInt();
			config.Add("FinalSimulationTime").IsNumber();
			config.Add("RandomNumberSeed").IsInt();
			config.Add("NumberOfMoleculeTypes").IsInt();

			JsonKeyPair microscopic_regions = config.Add("MicroscopicRegions");
			microscopic_regions.IsStructure();
			size_t n = microscopic_regions.GetArraySize();
			
			for (size_t i = 0; i < n; i++)
			{
				microscopic_regions.SetIndex(i);

				microscopic_regions.Add("Names").IsString();
				microscopic_regions.Add("SurfaceType").IsString();
				microscopic_regions.Add("DiffusionCoefficients").IsArray();
				microscopic_regions.Add("NumberOfSubvolumes").IsArray();
				microscopic_regions.Add("TimeStep").IsNumber();
				microscopic_regions.Add("Priority").IsInt();
				JsonKeyPair shape = microscopic_regions.Add("Shape");
				shape.IsString();
				std::string shape_type = shape.GetJson().get<std::string>();
				if (shape_type == "Box")
				{
					microscopic_regions.Add("Origin").IsArrayOfNumbers();
					microscopic_regions.Add("Length").IsArrayOfNumbers();
					//IsArrayOfType(microscopic_region, "Length", &ConfigImporter::IsInt);
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
	};
}