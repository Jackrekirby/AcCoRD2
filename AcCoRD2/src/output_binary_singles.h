#pragma once
#include <string> // for std::string
#include <fstream> // for std::ofstream

namespace AcCoRD
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

		// copy constructor, useful if class stored in vector as ofstream are not copyable
		OutputBinarySingles(const OutputBinarySingles& other)
			: file_path(other.file_path), file(other.file_path, std::ofstream::binary)
		{

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