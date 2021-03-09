// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

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
				LOG_CRITICAL("OutputBinarySingles could not open file <{}>", file_path);
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

		void NewFile(std::string file_path)
		{
			file.close();
			file.clear();
			file.open(file_path);
			if (!file.is_open())
			{
				LOG_CRITICAL("OutputBinaryVectors could not open file <{}>", file_path);
			}
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