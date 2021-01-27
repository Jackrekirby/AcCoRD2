#pragma once
#include "active_actor.h"
#include "output_binary_vectors.h"

namespace accord
{
	class ActiveActorRandomBits : public ActiveActor
	{
	public:
		ActiveActorRandomBits(double action_interval, double release_interval, double slot_interval,
			double bit_probability, int n_modulation_bits,
			const std::vector<int>& release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& microscopic_regions,
			const std::vector<mesoscopic::Region*>& mesoscopic_regions, std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, const ActiveActorID& id);

		void Run();

		void GenerateSymbol();

		void NextRealisation();

	private:
		int symbol;
		double slot_interval;
		int n_modulation_bits;
		double bit_probability;
		OutputBinaryVectors<int> symbol_file;

		int n_releases_per_interval;
		int release_index;

		std::string CreateSymbolFilePath();
	};
}