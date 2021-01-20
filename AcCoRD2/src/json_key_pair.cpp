#include "pch.h"
#include "json_key_pair.h"

namespace accord
{
	JsonKeyPair::JsonKeyPair()
		: keys(""), index(0), has_index(false)
	{

	}

	JsonKeyPair::JsonKeyPair(const Json& j)
		: j(j), keys(""), index(0), has_index(false)
	{

	}

	JsonKeyPair::JsonKeyPair(const JsonKeyPair& json_key_pair, const std::string& key)
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


	bool JsonKeyPair::IsKey(const std::string& key) const
	{
		return (GetJson().contains(key));
	}

	void JsonKeyPair::IsInRange(int min, int max)
	{
		int value = GetJson().get<int>();
		if (!(value >= min && value <= max))
		{
			LOG_ERROR("The key <{}> had value = {} but {} <= value <= {}", Log(), value, min, max);
			throw std::exception();
		}
	}

	void JsonKeyPair::ThrowIfNotKey(const std::string& key) const
	{
		if (!GetJson().contains(key))
		{
			LOG_ERROR("The key <{}> could not be found", Log(key));
			throw std::exception();
		}
	}

	JsonKeyPair JsonKeyPair::Add(const std::string& key) const
	{
		ThrowIfNotKey(key);
		return JsonKeyPair((*this), key);
	}

	void JsonKeyPair::SetIndex(size_t index)
	{
		this->index = index;
		has_index = true;
	}

	std::string JsonKeyPair::Log(const std::string& key) const
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

	std::string JsonKeyPair::Log() const
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

	const std::string& JsonKeyPair::GetKeys() const
	{
		return keys;
	}

	const Json& JsonKeyPair::GetJson() const
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

	void JsonKeyPair::ThrowIncorrectType(const std::string& type)
	{
		std::string keys;
		LOG_ERROR("<{}> expected {} but was type {}", Log(), type, std::string(GetJson().type_name()));

		throw std::exception();
	}

	size_t JsonKeyPair::GetArraySize() const
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
			LOG_CRITICAL("Expected array or object for key <{}> but was type {}", Log(), std::string(GetJson().type_name()));
			throw std::exception();
		}
	}


	void JsonKeyPair::IsBool()
	{
		if (!GetJson().is_boolean())
		{
			ThrowIncorrectType("boolean");
		}
	}

	void JsonKeyPair::IsInt()
	{
		if (!GetJson().is_number_integer())
		{
			ThrowIncorrectType("integer");
		}
	}

	void JsonKeyPair::IsFloat()
	{
		if (!GetJson().is_number_float())
		{
			ThrowIncorrectType("float");
		}
	}

	void JsonKeyPair::IsNumber()
	{
		if (!GetJson().is_number())
		{
			ThrowIncorrectType("float or int");
		}
	}

	void JsonKeyPair::IsString()
	{
		if (!GetJson().is_string())
		{
			ThrowIncorrectType("string");
		}
	}

	void JsonKeyPair::IsArray()
	{
		if (!GetJson().is_array())
		{
			ThrowIncorrectType("array");
		}
	}

	void JsonKeyPair::IsObject()
	{
		if (!GetJson().is_object())
		{
			ThrowIncorrectType("object");
		}
	}

	void JsonKeyPair::IsStructure()
	{
		if (!j.is_structured())
		{
			ThrowIncorrectType("array or object");
		}
	}


	void JsonKeyPair::IsArrayOfType(void(JsonKeyPair::* IsType)())
	{
		IsArray();
		size_t n = GetArraySize();
		for (size_t i = 0; i < n; i++)
		{
			SetIndex(i);
			(this->*IsType)();
		}
		has_index = false;
	}

	void JsonKeyPair::IsArrayOfBools()
	{
		IsArrayOfType(&JsonKeyPair::IsBool);
	}

	void JsonKeyPair::IsArrayOfInts()
	{
		IsArrayOfType(&JsonKeyPair::IsInt);
	}

	void JsonKeyPair::IsArrayOfFloats()
	{
		IsArrayOfType(&JsonKeyPair::IsFloat);
	}

	void JsonKeyPair::IsArrayOfNumbers()
	{
		IsArrayOfType(&JsonKeyPair::IsNumber);
	}

	void JsonKeyPair::IsArrayOfStrings()
	{
		IsArrayOfType(&JsonKeyPair::IsString);
	}

	void JsonKeyPair::IsArrayOfArrays()
	{
		IsArrayOfType(&JsonKeyPair::IsArray);
	}

	void JsonKeyPair::IsArrayOfObjects()
	{
		IsArrayOfType(&JsonKeyPair::IsObject);
	}

	void JsonKeyPair::IsArrayOfStructures()
	{
		IsArrayOfType(&JsonKeyPair::IsStructure);
	}
}