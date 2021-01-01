#pragma once
#include "active_actor2.h"
#include "output_binary_vectors.h"

namespace accord
{
	class ActiveActorRandomBits : public ActiveActor2
	{
	public:
		ActiveActorRandomBits(double action_interval, double release_interval, double slot_interval,
			double bit_probability, int n_modulation_bits, std::string file_path,
			MoleculeIDs release_molecules, int modulation_strength, std::vector<microscopic::Region*> regions,
			std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, EventQueue* event_queue, ActiveActorID id);

		void Run();

		void GenerateSymbol();

	private:
		int symbol;
		double slot_interval;
		int n_modulation_bits;
		double bit_probability;
		OutputBinaryVectors<int> symbol_file;

		int n_releases_per_interval;
		int release_index;
	};
}