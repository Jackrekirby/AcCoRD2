#include "logger.h"
#include "output_binary_singles.h"
#include "output_binary_vectors.h"
#include "math/vec3d.h"

namespace accord
{
	void WriteBinarySingles()
	{
		{
			using OBS = accord::OutputBinarySingles<int>;
			OBS obs("D:/dev/binaries/b.bin");
			for (int i = 1; i <= 5; i++)
			{
				obs.Write((i % 2) == 1);
			}
			obs.Close();
		}
		{
			using OBS = accord::OutputBinarySingles<double>;
			OBS obs("D:/dev/binaries/t.bin");
			for (double i = 1; i <= 5; i += 0.26384)
			{
				obs.Write(i);
			}
			obs.Close();
		}
		{
			using OBV = accord::OutputBinaryVectors<accord::math::Vec3d>;
			using OBS = accord::OutputBinarySingles<size_t>;
			OBV obv("D:/dev/binaries/p.bin");
			OBS obs("D:/dev/binaries/c.bin");
			std::vector<accord::math::Vec3d> positions;

			for (int n = 0; n < 5; n++)
			{
				for (double i = 0; i < n; i++)
				{
					positions.emplace_back(i * 3, i * 3 + 1, i * 3 + 2);
					LOG_INFO(positions.back());
				}
				obv.Write(positions);
				obs.Write(positions.size());
				positions.clear();
			}

			obv.Close();
			obs.Close();
		}
	}

	void OutputBinaryTest()
	{
		using OBSd = accord::OutputBinarySingles<double>;

		OBSd obs("logs/binary_test_singles.bin");

		for (int i = 1; i <= 5; i++)
		{
			obs.Write(i);
		}

		obs.Close(); // would automatically be closed by deconstructor

		// check copy constructor does not work
		//OBSd obs2 = obs;
		//OBSd obs3(obs);
		// obs3 would overwrite obs which has already closed

		// vector will resize, calling the move constructor of obs
		std::vector<OBSd> binaries;
		std::string file_path = "logs/binary_test_copy.bin";
		binaries.emplace_back(file_path);
		binaries.emplace_back(file_path);
		binaries.emplace_back(file_path);
		binaries.emplace_back(file_path);
		binaries.emplace_back(file_path);

		// last file to close has priority of writing to file
		double i = 0;
		for (auto& b : binaries)
		{
			i++;
			b.Write(i);
			// close in ascending order
			b.Close();
		}

		// close in reverse order
		for (size_t i = binaries.size(); i > 0; i--)
		{
			// last file to close has priority of writing to file
			binaries.at(i-1).Close();
		}
	}

	void OutputBinaryVectorTest()
	{
		using OBVd = accord::OutputBinaryVectors<double>;

		OBVd obs("logs/binary_test_vectors.bin");

		std::vector<double> v = { 1.0, 2.3, -5.6, 9.873 };
		std::vector<double> v2 = { -8.74, 37.4, 1.21 };

		obs.Write(v);
		obs.Write(v2);
		obs.Write(v2);
		obs.Write(v);

		obs.Close(); // would automatically be closed by deconstructor
	}
} // namespace accord