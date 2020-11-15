#pragma once
//#include <string> // for std::string
#include <fstream> // for std::ofstream

#include "pch.h"

namespace accord
{
	template<typename T>
	class OutputBinarySingles
	{
	public:
		OutputBinarySingles(std::string file_path)
			: file_path(file_path), file(file_path, std::ofstream::binary)
		{
			if (!file.is_open())
			{
				LOG_ERROR("OutputBinarySingles could not open file <{}>", file_path);
			}
		}

		// move constructor
		OutputBinarySingles(OutputBinarySingles&& other) noexcept
		{
			file_path = std::move(other.file_path);
			file = std::move(other.file);
		}

		~OutputBinarySingles()
		{
			Close();
		}
		
		void Write(const T value)
		{
			file.write(reinterpret_cast<const char*>(&value), sizeof(T));
		}
		
		void Close()
		{
			file.close();
		}

		std::string_view GetFilePath()
		{
			return file_path;
		}

	private:
		std::string file_path;
		std::ofstream file;
	};

}