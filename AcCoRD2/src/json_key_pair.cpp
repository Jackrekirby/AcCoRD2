// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

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

	JsonKeyPair JsonKeyPair::EnterIndex()
	{
		JsonKeyPair jkp;
		jkp.j = GetJson();
		jkp.keys = keys;

		if (has_index)
		{
			jkp.keys.append(fmt::format("[{}]", index));
		}

		return jkp;
	}

	bool JsonKeyPair::IsKey(const std::string& key) const
	{
		return (GetJson().contains(key));
	}

	JsonKeyPair& JsonKeyPair::IsInRange(int min, int max)
	{
		if (GetJson().is_array())
		{
			size_t n = GetJson().size();
			for (size_t i = 0; i < n; i++)
			{
				SetIndex(i);
				IsInRange(min, max);
			}
			has_index = false;
		}
		else
		{
			int value = GetJson().get<int>();
			if (!(value >= min && value <= max))
			{
				LOG_ERROR("The key <{}> had value = {} but {} <= value <= {}", Log(), value, min, max);
				throw std::exception();
			}
		}
		return *this;
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

	JsonKeyPair& JsonKeyPair::IsPositive()
	{
		IsGreaterThan(0.0);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsNonNegative()
	{
		IsGreaterOrEqualTo(0.0);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::HasSize(size_t size)
	{
		//LOG_INFO("{} {} {}", Log(), size, GetJson().size());
		if (size != GetJson().size())
		{
			LOG_ERROR("Expected <{}> to have a size of {} but had size {}", Log(), size, GetJson().size());

			throw std::exception();
		}
		return *this;
	}


	JsonKeyPair& JsonKeyPair::IsBool()
	{
		if (!GetJson().is_boolean())
		{
			ThrowIncorrectType("boolean");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsInt()
	{
		if (!GetJson().is_number_integer())
		{
			ThrowIncorrectType("integer");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsFloat()
	{
		if (!GetJson().is_number_float())
		{
			ThrowIncorrectType("float");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsNumber()
	{
		if (!GetJson().is_number())
		{
			ThrowIncorrectType("float or int");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsString()
	{
		if (!GetJson().is_string())
		{
			ThrowIncorrectType("string");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArray()
	{
		if (!GetJson().is_array())
		{
			ThrowIncorrectType("array");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsObject()
	{
		if (!GetJson().is_object())
		{
			ThrowIncorrectType("object");
		}
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsStructure()
	{
		if (!j.is_structured())
		{
			ThrowIncorrectType("array or object");
		}
		return *this;
	}

	void JsonKeyPair::IsArrayOfType(JsonKeyPair&(JsonKeyPair::* IsType)())
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

	JsonKeyPair& JsonKeyPair::IsArrayOfBools()
	{
		IsArrayOfType(&JsonKeyPair::IsBool);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfInts()
	{
		IsArrayOfType(&JsonKeyPair::IsInt);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfFloats()
	{
		IsArrayOfType(&JsonKeyPair::IsFloat);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfNumbers()
	{
		IsArrayOfType(&JsonKeyPair::IsNumber);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfStrings()
	{
		IsArrayOfType(&JsonKeyPair::IsString);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfArrays()
	{
		IsArrayOfType(&JsonKeyPair::IsArray);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfObjects()
	{
		IsArrayOfType(&JsonKeyPair::IsObject);
		return *this;
	}

	JsonKeyPair& JsonKeyPair::IsArrayOfStructures()
	{
		IsArrayOfType(&JsonKeyPair::IsStructure);
		return *this;
	}
}