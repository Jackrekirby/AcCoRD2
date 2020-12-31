#include "pch.h"
#include "active_actor_random_bits.h"

namespace accord
{
	ActiveActorRandomBits::ActiveActorRandomBits(double action_interval, double release_interval, double slot_interval,
		double bit_probability, int n_modulation_bits, std::string file_path,
		MoleculeIDs release_molecules, int modulation_strength, std::vector<microscopic::Region*> regions,
		std::unique_ptr<ActiveActorShape> shape,
		double start_time, int priority, EventQueue* event_queue, ActiveActorID id)
		: ActiveActor2(action_interval, release_interval, release_molecules, modulation_strength, regions, std::move(shape),
			start_time, priority, event_queue, id), bit_probability(bit_probability), n_modulation_bits(n_modulation_bits),
		symbol_file(file_path)
	{
		
	}

	void ActiveActorRandomBits::Run()
	{
		ReleaseMolecules(symbol * modulation_strength);
		if (SetNextReleaseTime(slot_interval))
		{
			GenerateSymbol();
		}
	};

	void ActiveActorRandomBits::GenerateSymbol()
	{
		std::vector<int> bits;
		bits.reserve(n_modulation_bits);
		symbol = 0;
		int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
		for (int i = 0; i < n_modulation_bits; i++)
		{
			int bit = (Random::GenerateRealUniform() < bit_probability);
			symbol += bit * power;
			//LOG_INFO("bit = {}, symbol = {}", bit, symbol);
			power /= 2;
			bits.emplace_back(bit);
		}
		symbol_file.Write(bits);
	}
}