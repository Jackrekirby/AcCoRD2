#pragma once
#include "pch.h"

namespace accord
{
	struct Vec3d;

	// takes a file or folder path and optional key and converts that file / files in that folder and subfolders 
	// from a binary format to JSON format.
	class BinaryToJson
	{
	public:
		static void Convert(std::string path, std::optional<std::string> key);
	private:
		typedef std::filesystem::directory_entry DirEntry;

		// the character used to seperate the identifiers in the simulation output file names. e.g. "simulation\s1\r0\p0_m0_c.bin"
		static const char file_name_delimiter = '_';

		// converts all files in a directory and subdirectories. If a key is provided only files which have a path which partially
		// matches the key are converted. E.g. base_directory = "simulation\s1", key = "m0" will convert all files in seed 1 with 
		// molecule type 0
		static void BinariesToJson(DirEntry base_directory, std::optional<std::string> key);

		// converts a single file from binary to json
		static void SingleBinaryToJson(DirEntry binary_file);

		// Compiles a list of paths to the binary files which are inside the directory and match the key, if a key is given.
		// This function is recursive, calling itself each time it enters a subdirectory of the base directory.
		static void FindBinaries(DirEntry base_directory, std::optional<std::string> key,
			const DirEntry& directory, std::vector<std::filesystem::directory_entry>& binary_files);

		// Is passed the path to a binary files. This function then works out what type of binary file it is so it can call
		// the correct conversion function (BitSequence, OberservationTimes, MoleculeCount or MoleculePositions)
		// Molecule position files require the corresponding molecule count file to be available
		// Returns true if the conversion from binary to json was successful
		static bool ConvertBinary(const DirEntry& entry);

		// Converts the bit sequence of an active actor from a binary file to json file.
		// Returns true if the conversion was successful
		static bool ConvertBitSequence(const std::string& file_path);

		// Converts the observation times of a passive actor from a binary file to json file
		// Returns true if the conversion was successful
		static bool ConvertObservationTimes(const std::string& file_path);

		// Converts the molecule count data of a passive actor from a binary file to json file
		// Returns true if the conversion was successful
		static bool ConvertMoleculeCounts(const std::string& file_path);

		// Converts the molecule position data of a passive actor from a binary file to json file
		// Requires the path of the molecule count file to also be passed
		// Returns true if the conversion was successful
		static bool ConvertMoleculePositions(const std::string& positions_file_path, const std::string& count_file_path);

		// Removes the '.bin' file extension from a file path and replaces it with a '.json' file extension
		static std::string ChangeBinForJsonFileExtension(const std::string& bin_path);

		// Takes a json object and outputs it to a json file
		static bool WriteJson(const std::string& json_file_path, const Json& j);

		// Converts any binary file into a vector of a specified type.
		// Function cannot convert booleans (it leads to read access violation). Recommend storing booleans as integers
		template <typename T> 
		static std::vector<T> ReadBinaryAsVector(std::string file_path);
	};

}