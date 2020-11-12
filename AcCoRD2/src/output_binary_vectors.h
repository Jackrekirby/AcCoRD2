#pragma once
#include <string> // for std::string
#include <fstream> // for std::ofstream

namespace AcCoRD
{
	template<typename T>
	class OutputBinaryVectors
	{
	public:
		OutputBinaryVectors(std::string file_path)
			: file_path(file_path), file(file_path, std::ofstream::binary)
		{
			if (!file.is_open())
			{
				LOG_ERROR("OutputBinaryVectors could not open file <{}>", file_path);
			}
		}

		// move constructor
		OutputBinaryVectors(OutputBinaryVectors&& other) noexcept
		{
			file_path = std::move(other.file_path);
			file = std::move(other.file);
		}

		~OutputBinaryVectors()
		{
			Close();
		}

		void Write(const std::vector<T>& vector)
		{
			size_t size = vector.size();
			if (size != 0)
			{
				file.write(reinterpret_cast<const char*>(&vector.at(0)), sizeof(T) * size);
			}
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