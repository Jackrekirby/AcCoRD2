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

		JsonKeyPair EnterIndex();

		JsonKeyPair Add(const std::string& key) const;


		std::string Log(const std::string& key) const;

		std::string Log() const;


		void SetIndex(size_t index);

		const std::string& GetKeys() const;

		const Json& GetJson() const;

		size_t GetArraySize() const;


		bool IsKey(const std::string& key) const;

		JsonKeyPair& IsInRange(int min, int max);
		


		JsonKeyPair& IsBool();

		JsonKeyPair& IsInt();

		JsonKeyPair& IsFloat();

		JsonKeyPair& IsNumber();

		JsonKeyPair& IsString();

		JsonKeyPair& IsArray();

		JsonKeyPair& IsObject();

		JsonKeyPair& IsStructure();


		void IsArrayOfType(JsonKeyPair&(JsonKeyPair::* IsType)());

		JsonKeyPair& IsArrayOfBools();

		JsonKeyPair& IsArrayOfInts();

		JsonKeyPair& IsArrayOfFloats();

		JsonKeyPair& IsArrayOfNumbers();

		JsonKeyPair& IsArrayOfStrings();

		JsonKeyPair& IsArrayOfArrays();

		JsonKeyPair& IsArrayOfObjects();

		JsonKeyPair& IsArrayOfStructures();


		JsonKeyPair& IsPositive();

		JsonKeyPair& IsNonNegative();

		template<typename T>
		JsonKeyPair& ExactNumMatchValue(T value, int matching)
		{
			if (GetJson().is_array())
			{
				size_t n = GetJson().size();
				int do_match = 0;
				for (size_t i = 0; i < n; i++)
				{
					SetIndex(i);
					do_match += static_cast<int>(value == GetJson().get<T>());
				}
				has_index = false;
				if (matching != do_match)
				{
					LOG_ERROR("Exactly {} of the values in array <{}> must have value {} but {} did", matching, Log(), value, do_match);
					throw std::exception();
				}
			}
			return *this;
		}

		template<typename T>
		JsonKeyPair& IsLessOrEqualTo(T max)
		{
			if (GetJson().is_array())
			{
				size_t n = GetJson().size();
				for (size_t i = 0; i < n; i++)
				{
					SetIndex(i);
					IsLessOrEqualTo(max);
				}
				has_index = false;
			}
			else
			{
				T value = GetJson().get<T>();
				if (!(value <= max))
				{
					LOG_ERROR("The key <{}> had value = {} but value <= {}", Log(), value, max);
					throw std::exception();
				}
			}
			return *this;
		}

		template<typename T>
		JsonKeyPair& IsLessThan(T max)
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
			else
			{
				T value = GetJson().get<T>();
				if (!(value < max))
				{
					LOG_ERROR("The key <{}> had value = {} but value < {}", Log(), value, max);
					throw std::exception();
				}
			}
			return *this;
		}

		template<typename T>
		JsonKeyPair& IsGreaterOrEqualTo(T min)
		{
			if (GetJson().is_array())
			{
				size_t n = GetJson().size();
				for (size_t i = 0; i < n; i++)
				{
					SetIndex(i);
					IsGreaterOrEqualTo(min);
				}
				has_index = false;
			}
			else
			{
				T value = GetJson().get<T>();
				if (!(value >= min))
				{
					LOG_ERROR("The key <{}> had value = {} but value >= {}", Log(), value, min);
					throw std::exception();
				}
			}
			return *this;
		}

		template<typename T>
		JsonKeyPair& IsGreaterThan(T min)
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
			}
			else
			{
				T value = GetJson().get<T>();
				if (!(value > min))
				{
					LOG_ERROR("The key <{}> had value = {} but value > {}", Log(), value, min);
					throw std::exception();
				}
			}
			return *this;
		}

		template<typename T>
		JsonKeyPair& IsOneOf(std::vector<T> values)
		{
			T value = GetJson().get<T>();
			if (std::find(values.begin(), values.end(), value) == values.end()) {
				LOG_ERROR("The key <{}> had value = {} but was expected to be one of [{}]", Log(), value, Log(values));
				throw std::exception();
			}
			return *this;
		}

		JsonKeyPair& HasSize(size_t size);

		template<typename T>
		JsonKeyPair& IsEachOneOf(std::vector<T> values)
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
			return *this;
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

		void ThrowIncorrectType(const std::string& type);

		void ThrowIfNotKey(const std::string& key) const;

	private:
		Json j;
		std::string keys;
		size_t index;
		bool has_index;


	};
}