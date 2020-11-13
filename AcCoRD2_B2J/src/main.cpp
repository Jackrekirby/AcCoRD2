#include "logger.h"
#include "json.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <filesystem>
#include <optional>

namespace accord
{
	// Require Vec3d for converting position files
	struct Vec3d
	{
		double x, y, z;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3d& v)
		{
			return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		}
	};

	void to_json(Json& j, const Vec3d& v)
	{
		j = { v.x, v.y, v.z };
	}

	template <typename T>
	// bool type not allowed, leads to read access violation.
	std::vector<T> BinaryToVector(std::string file_path)
	{
		std::ifstream input(file_path, std::ios::binary);
		if (input.is_open())
		{
			std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
			std::vector<T> vec(buffer.size() / sizeof(T));
			LOG_TRACE("buffer size = {}, type size = {}, vec size = {}", buffer.size(), sizeof(T), vec.size());
			// reinterpret char (byte) vector as T vector
			if (buffer.size() != 0)
			{
				std::memcpy(&vec[0], &buffer[0], buffer.size());
			}
			return vec;
		}
		else
		{
			LOG_WARN("File <{}> could not be opened");
			return {};
		}
	}

	void GetBinaryFilePathsInDirectory(std::string dir_path, std::vector<std::string>& file_paths)
	{
		for (const auto& entry : std::filesystem::directory_iterator(dir_path))
		{
			if (entry.is_directory())
			{
				LOG_TRACE("Directory = <{}>", entry.path());
				GetBinaryFilePathsInDirectory(entry.path().string(), file_paths);
			}
			else if (entry.is_regular_file() && entry.path().extension() == ".bin")
			{
				LOG_DEBUG("Binary File = <{}>", entry.path());
				file_paths.emplace_back(entry.path().string());
			}
		}
	}

	void RemoveFilesNotMatchingKey(std::string dir_path, std::vector<std::string>& file_paths, std::string key)
	{
		auto dir_path_length = dir_path.length();

		for (auto path = file_paths.begin(); path != file_paths.end();)
		{
			std::string relative_path = path->substr(dir_path_length);
			if (relative_path.find(key) == std::string::npos)
			{
				path = file_paths.erase(path);  // Returns new iterator to continue from
			}
			else
			{
				++path;
			}
		}
	}

	std::string SwitchBinForJsonFileExtension(std::string bin_file_path)
	{
		return bin_file_path.substr(0, bin_file_path.length() - 3) + "json";
	}

	bool WriteJson(std::string json_file_path, const Json& j)
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

	void ConvertBitSequence(std::string file_path)
	{
		std::vector<int> bit_sequence = BinaryToVector<int>(file_path);
		std::string json_file_path = SwitchBinForJsonFileExtension(file_path);
		if (WriteJson(json_file_path, Json(bit_sequence)))
		{
			LOG_INFO("Saved Bit Sequence to <{}>", json_file_path);
		}
	}

	void ConvertObservationTimes(std::string file_path)
	{
		std::vector<double> times = BinaryToVector<double>(file_path);
		std::string json_file_path = SwitchBinForJsonFileExtension(file_path);
		if (WriteJson(json_file_path, Json(times)))
		{
			LOG_INFO("Saved Observation Times to <{}>", json_file_path);
		}
	}

	void ConvertMoleculeCounts(std::string file_path)
	{
		std::vector<size_t> counts = BinaryToVector<size_t>(file_path);
		std::string json_file_path = SwitchBinForJsonFileExtension(file_path);
		if (WriteJson(json_file_path, Json(counts)))
		{
			LOG_INFO("Saved Molecule Counts to <{}>", json_file_path);
		}
	}

	void ConvertMoleculePositions(std::string positions_file_path, std::string count_file_path)
	{
		std::vector<Vec3d> positions = BinaryToVector<Vec3d>(positions_file_path);
		std::vector<size_t> counts = BinaryToVector<size_t>(count_file_path);

		Json json;
		size_t count_sum = 0;
		for (size_t i = 0; i < counts.size(); i++)
		{
			auto& count = counts.at(i);
			json[i] = std::vector<Vec3d>(positions.begin() + count_sum, positions.begin() + count_sum + count);
			count_sum += count;
		}

		std::string json_file_path = SwitchBinForJsonFileExtension(positions_file_path);
		if (WriteJson(json_file_path, json))
		{
			LOG_INFO("Saved Molecule Positions to <{}>", json_file_path);
		}
	}

	void SortAndConvertBinaryFile(std::string file_path)
	{
		std::string file_type = file_path.substr(file_path.length() - 5, 1);

		if (file_type == "p")
		{
			std::string count_file_path = file_path.substr(0, file_path.length() - 5) + "c.bin";
			if (std::filesystem::exists(count_file_path))
			{
				ConvertMoleculePositions(file_path, count_file_path);
			}
			else
			{
				LOG_WARN("Could not convert count file <{}> for correcsponding position file <{}>", count_file_path, file_path);
			}
			
		}
		else if (file_type == "c")
		{
			ConvertMoleculeCounts(file_path);
		}
		if (file_type == "b")
		{
			ConvertBitSequence(file_path);
		}
		else if (file_type == "t")
		{
			LOG_DEBUG("time");
			ConvertObservationTimes(file_path);
		}
	}

	void ConvertBinariesToJsonFiles(std::string dir_path, std::optional<std::string> key)
	{
		std::vector<std::string> file_paths;
		LOG_INFO("Searching for available Binary Files in Directory <{}>", dir_path);
		GetBinaryFilePathsInDirectory(dir_path, file_paths);

		if (file_paths.size() > 0)
		{
			if (key.has_value())
			{
				LOG_INFO("Removing Binary Files not matching key <{}>", key.value());
				RemoveFilesNotMatchingKey(dir_path, file_paths, key.value());
			}
			if (file_paths.size() > 0)
			{


				LOG_INFO("Converting Binary Files to Json");
				for (auto& file_path : file_paths)
				{
					SortAndConvertBinaryFile(file_path);
				}
			}
			else
			{
				LOG_WARN("No Binary files found in directory matching key");
			}
		}
		else
		{
			LOG_WARN("No Binary files found in directory");
		}
	}
}

int main(int argc, char** argv)
{
	accord::Logger::Initialise("log.txt");
	LOG_INFO("AcCoRD2 Binary To Json Conversion Tool");

	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	std::vector<std::string> args(argv, argv + argc);

	switch (args.size())
	{
	case 2:
		// Convert all files in directory or a single file
		if (std::filesystem::is_directory(args.at(1)))
		{
			accord::ConvertBinariesToJsonFiles(args.at(1), std::nullopt);
		}
		else if (std::filesystem::is_regular_file(args.at(1)))
		{
			accord::SortAndConvertBinaryFile(args.at(1));
		}
		else
		{
			LOG_WARN("Argument provided must be a directory or file ({})", args.at(1));
		}
		break;
	case 3:
		// Convert all files in a directory with matching key
		if (std::filesystem::is_directory(args.at(1)))
		{
			LOG_DEBUG("{}, {}", args.at(1), args.at(2));
			accord::ConvertBinariesToJsonFiles(args.at(1), args.at(2));
		}
		break;
	default:
		LOG_WARN("Incorrect number of arguments provided ({})", args.size());
		return 0;
	}

	LOG_INFO("Conversion Complete");
}