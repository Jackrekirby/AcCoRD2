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

	class BinaryToJson
	{	
	public:
		typedef std::filesystem::directory_entry DirEntry;
		BinaryToJson(std::string path, std::optional<std::string> key)
		{
			std::filesystem::directory_entry entry(path);

			if (entry.is_directory())
			{
				BinariesToJson(entry, key);
			}
			else if (entry.path().extension() != ".bin")
			{
				SingleBinaryToJson(entry);
			}
			else
			{
				LOG_WARN("Path must be a directory or binary file ({})", path);
			}
		}
	private:
		static const char file_name_delimiter = '_';

		void BinariesToJson(DirEntry base_directory, std::optional<std::string> key)
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

			LOG_INFO("Found {} file(s) to convert", binary_files.size());
			LOG_INFO("List of converted file(s):");

			for (auto& entry : binary_files)
			{
				ConvertBinary(entry);
				LOG_INFO(std::filesystem::relative(entry, base_directory).string());
			}

			LOG_INFO("All file(s) converted");
		}

		void SingleBinaryToJson(DirEntry binary_file)
		{
			LOG_INFO("Starting conversion of <{}>", binary_file.path().string());

			ConvertBinary(binary_file);

			LOG_INFO("File converted");
		}

		void FindBinaries(DirEntry base_directory, std::optional<std::string> key,
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
						LOG_DEBUG("Binary File = <{}>", relative_path);
						binary_files.emplace_back(entry);
					}
				}
			}
		}

		bool ConvertBinary(const DirEntry& entry)
		{
			std::string file_path = entry.path().string();
			std::string file_type = file_path.substr(file_path.rfind(file_name_delimiter) + 1);
			if (file_type == "p.bin")
			{
				// remove position "p.bin" file type and replace with count "c.bin" file type
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
			else if (file_type == "p.bin")
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
				LOG_TRACE("Other binary file type <{}>", file_path);
				return false;
			}
		}


		bool ConvertBitSequence(const std::string& file_path)
		{
			std::vector<int> bit_sequence = ReadBinaryAsVector<int>(file_path);
			std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
			return WriteJson(json_file_path, Json(bit_sequence));
		}

		bool ConvertObservationTimes(const std::string& file_path)
		{
			std::vector<double> times = ReadBinaryAsVector<double>(file_path);
			std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
			return WriteJson(json_file_path, Json(times));
		}

		bool ConvertMoleculeCounts(const std::string& file_path)
		{
			std::vector<size_t> counts = ReadBinaryAsVector<size_t>(file_path);
			std::string json_file_path = ChangeBinForJsonFileExtension(file_path);
			return WriteJson(json_file_path, Json(counts));
		}

		bool ConvertMoleculePositions(const std::string& positions_file_path, const std::string& count_file_path)
		{
			std::vector<Vec3d> positions = ReadBinaryAsVector<Vec3d>(positions_file_path);
			std::vector<size_t> counts = ReadBinaryAsVector<size_t>(count_file_path);

			Json json;
			size_t count_sum = 0;

			for (size_t i = 0; i < counts.size(); i++)
			{
				auto& count = counts.at(i);
				json[i] = std::vector<Vec3d>(positions.begin() + count_sum, positions.begin() + count_sum + count);
				count_sum += count;
			}

			std::string json_file_path = ChangeBinForJsonFileExtension(positions_file_path);
			return WriteJson(json_file_path, json);
		}


		std::string ChangeBinForJsonFileExtension(const std::string& bin_path)
		{
			return bin_path.substr(0, bin_path.length() - 3) + "json";
		}

		bool WriteJson(const std::string& json_file_path, const Json& j)
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

		template <typename T> // bool type not allowed, leads to read access violation.
		std::vector<T> ReadBinaryAsVector(std::string file_path)
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
	};

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
			LOG_INFO("Saved bit sequence to <{}>", std::filesystem::path(json_file_path).relative_path());
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
		if (!std::filesystem::is_directory(dir_path))
		{
			LOG_WARN("Search directory is invalid ({})", dir_path);
			return;
		}

		std::vector<std::string> file_paths;
		LOG_INFO("Searching for binary files in directory <{}>", dir_path);
		GetBinaryFilePathsInDirectory(dir_path, file_paths);

		if (file_paths.size() > 0)
		{
			if (key.has_value())
			{
				LOG_INFO("Removing binary files not matching key <{}>", key.value());
				RemoveFilesNotMatchingKey(dir_path, file_paths, key.value());
			}

			if (file_paths.size() == 0)
			{
				LOG_WARN("No binary files found in directory matching key");
				return;
			}
	
			LOG_INFO("Converting binary files to json");
			for (auto& file_path : file_paths)
			{
				SortAndConvertBinaryFile(file_path);
			}
		}
		else
		{
			LOG_WARN("No binary files found in directory");
		}
	}
}

void old_version(int argc, char** argv)
{
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
		return;
	}

	LOG_INFO("Conversion Complete");
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
	{
		accord::BinaryToJson j(args.at(1), {});
		return 0;
	}
	case 3:
	{
		accord::BinaryToJson j(args.at(1), args.at(2));
		return 0;
	}
	default:
		LOG_WARN("Incorrect number of arguments provided ({})", args.size());
		return 0;
	}
}