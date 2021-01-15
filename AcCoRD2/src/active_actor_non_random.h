#pragma once
#include "active_actor2.h"
#include "output_binary_vectors.h"

// bit sequence only saved for realisation 0
namespace accord
{
	class ActiveActorNonRandom : public ActiveActor2
	{
	public:
		ActiveActorNonRandom(double action_interval, double release_interval, double slot_interval,
			std::vector<int> bit_sequence, int n_modulation_bits,
			MoleculeIDs release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& micro_regions,
			const std::vector<mesoscopic::Region*>& meso_regions, std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, const ActiveActorID& id);

		void Run();

		void GenerateSymbol();

		void NextRealisation();

		//bool SetNextReleaseTime();

	private:
		int symbol;
		int symbol_index;
		double slot_interval;
		int n_modulation_bits;
		std::vector<int> bit_sequence;

		int n_releases_per_interval;
		int release_index;

		std::string CreateSymbolFilePath();
	};
}