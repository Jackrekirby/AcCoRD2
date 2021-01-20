#pragma once
#include "pch.h"
#include <sstream>

namespace accord
{
	class JsonKeyPair
	{
	public:
		JsonKeyPair();

		JsonKeyPair(const Json& j);

		JsonKeyPair(const JsonKeyPair& json_key_pair, const std::string& key);

		JsonKeyPair Add(const std::string& key) const;


		std::string Log(const std::string& key) const;

		std::string Log() const;


		void SetIndex(size_t index);

		const std::string& GetKeys() const;

		const Json& GetJson() const;

		size_t GetArraySize() const;


		bool IsKey(const std::string& key) const;

		void IsInRange(int min, int max);
		

		template<typename T>
		void IsLessOrEqualTo(T max)
		{
			T value = GetJson().get<T>();
			if (!(value <= max))
			{
				LOG_ERROR("The key <{}> had value = {} but value <= {}", Log(), value, max);
				throw std::exception();
			}
		}

		template<typename T>
		void IsLessThan(T max)
		{
			if (GetJson().is_array())
			{
				size_t n = GetJson().size();
				for (size_t i = 0; i < n; i++)
				{
					SetIndex(i);
					IsLessThan(max);
				}
				has_index = false;
			}
			T value = GetJson().get<T>();
			if (!(value < max))
			{
				LOG_ERROR("The key <{}> had value = {} but value < {}", Log(), value, max);
				throw std::exception();
			}
		}

		template<typename T>
		void IsGreaterOrEqualTo(T min)
		{
			T value = GetJson().get<T>();
			if (!(value >= min))
			{
				LOG_ERROR("The key <{}> had value = {} but value >= {}", Log(), value, min);
				throw std::exception();
			}
		}

		void IsPositive()
		{
			IsGreaterThan(0);
		}

		template<typename T>
		void IsGreaterThan(T min)
		{
			if (GetJson().is_array())
			{
				size_t n = GetJson().size();
				for (size_t i = 0; i < n; i++)
				{
					SetIndex(i);
					IsGreaterThan(min);
				}
				has_index = false;
				return;
			}
			T value = GetJson().get<T>();
			if (!(value > min))
			{
				LOG_ERROR("The key <{}> had value = {} but value > {}", Log(), value, min);
				throw std::exception();
			}
		}

		template<typename T>
		std::string Log(std::vector<T> values)
		{
			std::stringstream ss;
			if (!values.empty())
			{
				for (auto value = values.begin(); value != values.end() - 1; ++value)
				{
					ss << *value << ", ";
				}
				ss << values.back();
			}
			return ss.str();
		}

		template<typename T>
		void IsEachOneOf(std::vector<T> values)
		{
			size_t n = GetArraySize();
			for (size_t i = 0; i < n; i++)
			{
				SetIndex(i);
				T value = GetJson().get<T>();
				if (std::find(values.begin(), values.end(), value) == values.end()) {
					LOG_ERROR("The key <{}> had value = {} but was expected to be one of [{}]", Log(), value, Log(values));
					throw std::exception();
				}
			}
		}

		void operator < (int max);

		void IsBool();

		void IsInt();

		void IsFloat();

		void IsNumber();

		void IsString();

		void IsArray();
	
		void IsObject();

		void IsStructure();


		void IsArrayOfType(void(JsonKeyPair::* IsType)());

		void IsArrayOfBools();

		void IsArrayOfInts();

		void IsArrayOfFloats();

		void IsArrayOfNumbers();

		void IsArrayOfStrings();

		void IsArrayOfArrays();

		void IsArrayOfObjects();

		void IsArrayOfStructures();
	private:
		Json j;
		std::string keys;
		size_t index;
		bool has_index;

		void ThrowIncorrectType(const std::string& type);

		void ThrowIfNotKey(const std::string& key) const;
	};
}