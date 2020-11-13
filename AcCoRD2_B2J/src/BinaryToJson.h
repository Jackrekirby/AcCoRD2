#pragma once
//#include "json.h"

#include <filesystem> // for std::filesystem
#include <string> // for std::string
#include <optional> // std::optional

namespace accord
{
	struct Vec3d;

	class BinaryToJson
	{
	public:
		static void Convert(std::string path, std::optional<std::string> key);
	private:
		typedef std::filesystem::directory_entry DirEntry;

		static const char file_name_delimiter = '_';

		static void BinariesToJson(DirEntry base_directory, std::optional<std::string> key);

		static void SingleBinaryToJson(DirEntry binary_file);

		static void FindBinaries(DirEntry base_directory, std::optional<std::string> key,
			const DirEntry& directory, std::vector<std::filesystem::directory_entry>& binary_files);

		static bool ConvertBinary(const DirEntry& entry);


		static bool ConvertBitSequence(const std::string& file_path);

		static bool ConvertObservationTimes(const std::string& file_path);

		static bool ConvertMoleculeCounts(const std::string& file_path);

		static bool ConvertMoleculePositions(const std::string& positions_file_path, const std::string& count_file_path);


		static std::string ChangeBinForJsonFileExtension(const std::string& bin_path);

		static bool WriteJson(const std::string& json_file_path, const Json& j);

		template <typename T> // bool type not allowed, leads to read access violation.
		static std::vector<T> ReadBinaryAsVector(std::string file_path);
	};

}