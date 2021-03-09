// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "binary_to_json.h"
#include "vec3d.h"

namespace accord
{
	void BinaryToJson::Convert(std::string path, std::optional<std::string> key)
	{
		std::filesystem::directory_entry entry(path);

		if (entry.is_directory())
		{
			BinariesToJson(entry, key);
		}
		else if (entry.path().extension() == ".bin")
		{
			SingleBinaryToJson(entry);
		}
		else
		{
			LOG_WARN("Path must be a directory or binary file <{}>", path);
		}
	}


	void BinaryToJson::BinariesToJson(DirEntry base_directory, std::optional<std::string> key)
	{
		if (key.has_value())
		{
			LOG_INFO("Searching directory <{}> for binary files which match key <{}>", base_directory.path().string(), key.value());
		}
		else
		{
			LOG_INFO("Searching directory <{}> for binary files", base_directory.path().string());
		}

		std::vector<DirEntry> binary_files;
		FindBinaries(base_directory, key, base_directory, binary_files);

		int n_files = static_cast<int>(binary_files.size());
		LOG_INFO("Found {} file(s) to convert. List of converted file(s):", n_files);
		int i = 1;
		for (auto& entry : binary_files)
		{
			ConvertBinary(entry);
			LOG_INFO("{}. {}", i++, std::filesystem::relative(entry, base_directory).string());
		}

		LOG_INFO("All file(s) converted");
	}


	void BinaryToJson::SingleBinaryToJson(DirEntry binary_file)
	{
		LOG_INFO("Starting conversion of <{}>", binary_file.path().string());

		ConvertBinary(binary_file);

		LOG_INFO("File converted");
	}

	void BinaryToJson::FindBinaries(DirEntry base_directory, std::optional<std::string> key,
		const DirEntry& directory, std::vector<std::filesystem::directory_entry>& binary_files)
	{
		for (const auto& entry : std::filesystem::directory_iterator(directory))
		{
			if (entry.is_directory())
			{
				LOG_TRACE("Directory = <{}>", std::filesystem::relative(entry, base_directory).string());
				FindBinaries(base_directory, key, entry, binary_files);
			}
			else if (entry.path().extension() == ".bin")
			{
				std::string relative_path = std::filesystem::relative(entry, base_directory).string();
				if (!key.has_value() || relative_path.find(key.value()) != std::string::npos)
				{
					LOG_DEBUG("Found binary file: {}", relative_path);
					binary_files.emplace_back(entry);
				}
			}
		}
	}

	bool BinaryToJson::ConvertBinary(const DirEntry& entry)
	{
		std::string file_path = entry.path().string();
		std::string file_type = file_path.substr(file_path.rfind(file_name_delimiter) + 1);
		if (file_type == "p.bin")
		{
			// removes position "p.bin" file type and replace with count "c.bin" file type
			std::string count_file_path = file_path.substr(0, file_path.length() - 5) + "c.bin";
			if (std::filesystem::exists(count_file_path))
			{
				return ConvertMoleculePositions(file_path, count_file_path);
			}
			else
			{
				LOG_WARN("Could not convert position file <{}>, as corresponding count file <{}> required", file_path, count_file_path);
				return false;
			}
		}
		else if (file_type == "c.bin")
		{
			return ConvertMoleculeCounts(file_path);
		}
		else if (file_type == "b.bin")
		{
			return ConvertBitSequence(file_path);
		}
		else if (file_type == "t.bin")
		{
			return ConvertObservationTimes(file_path);
		}
		else
		{
			LOG_TRACE("Binary not of required type <{}>", file_path);
			return false;
		}
	}


	bool BinaryToJson::ConvertBitSequence(const std::string& file_path)
	{
		std::vector<int> bit_sequence = ReadBinaryAsVector<int>(file_path);
		std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
		return WriteJson(json_file_path, Json(bit_sequence));
	}

	bool BinaryToJson::ConvertObservationTimes(const std::string& file_path)
	{
		std::vector<double> times = ReadBinaryAsVector<double>(file_path);
		std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
		return WriteJson(json_file_path, Json(times));
	}

	bool BinaryToJson::ConvertMoleculeCounts(const std::string& file_path)
	{
		std::vector<int> counts = ReadBinaryAsVector<int>(file_path);
		std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
		return WriteJson(json_file_path, Json(counts));
	}

	bool BinaryToJson::ConvertMoleculePositions(const std::string& positions_file_path, const std::string& count_file_path)
	{
		std::vector<Vec3d> positions = ReadBinaryAsVector<Vec3d>(positions_file_path);
		std::vector<int> counts = ReadBinaryAsVector<int>(count_file_path);

		Json json;
		int count_sum = 0;

		for (int i = 0; i < counts.size(); i++)
		{
			auto& count = counts.at(i);
			json[i] = std::vector<Vec3d>(positions.begin() + count_sum, positions.begin() + count_sum + count);
			count_sum += count;
		}

		std::string json_file_path = ChangeBinForJsonFileExtension(positions_file_path);
		return WriteJson(json_file_path, json);
	}


	std::string BinaryToJson::ChangeBinForJsonFileExtension(const std::string& bin_path)
	{
		return bin_path.substr(0, bin_path.length() - 3) + "json";
	}

	bool BinaryToJson::WriteJson(const std::string& json_file_path, const Json& j)
	{
		std::ofstream json_file(json_file_path);
		if (json_file.is_open())
		{
			json_file << j;
			return true;
		}
		else
		{
			LOG_WARN("File <{}> could not be opened");
			return false;
		}
	}

	template <typename T>
	std::vector<T> BinaryToJson::ReadBinaryAsVector(std::string file_path)
	{
		std::ifstream input(file_path, std::ios::binary);
		if (input.is_open())
		{
			std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
			std::vector<T> vector(buffer.size() / sizeof(T));
			LOG_TRACE("Binary import information: buffer size = {}, type size = {}, vector size = {}", buffer.size(), sizeof(T), vector.size());
			// reinterpret char (byte) vector as T vector
			if (buffer.size() != 0)
			{
				std::memcpy(&vector[0], &buffer[0], buffer.size());
			}
			return vector;
		}
		else
		{
			LOG_WARN("File <{}> could not be opened");
			return {};
		}
	}
}