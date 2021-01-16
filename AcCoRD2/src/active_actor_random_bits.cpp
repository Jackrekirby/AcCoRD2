#include "pch.h"
#include "active_actor_random_bits.h"
#include "environment.h"

namespace accord
{
	ActiveActorRandomBits::ActiveActorRandomBits(double action_interval, double release_interval, double slot_interval,
		double bit_probability, int n_modulation_bits,
		MoleculeIDs release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& micro_regions,
		const std::vector<mesoscopic::Region*>& meso_regions, std::unique_ptr<ActiveActorShape> shape,
		double start_time, int priority, const ActiveActorID& id)
		: ActiveActor(action_interval, release_interval, release_molecules, modulation_strength, micro_regions, meso_regions, std::move(shape),
			start_time, priority, id), bit_probability(bit_probability), n_modulation_bits(n_modulation_bits),
		symbol_file(CreateSymbolFilePath()), n_releases_per_interval(static_cast<int>(release_interval / slot_interval)), release_index(0),
		slot_interval(slot_interval), symbol(0)
	{
		
	}

	void ActiveActorRandomBits::Run()
	{
		if (release_index == 0)
		{
			GenerateSymbol();
		}

		if (release_index < n_releases_per_interval)
		{
			//LOG_INFO("Releasing Molecule {}", symbol * modulation_strength);
			ReleaseMolecules(symbol * modulation_strength);
			release_index++;
			local_time += slot_interval;
		}
		else
		{
			//LOG_INFO("wait until next action interval", local_time);
			last_action_time += action_interval;
			local_time = last_action_time;
			release_index = 0;
		}

		SetEventTime(local_time);
	};

	void ActiveActorRandomBits::GenerateSymbol()
	{
		std::vector<int> bits;
		bits.reserve(n_modulation_bits);
		symbol = 0;
		int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
		for (int i = 0; i < n_modulation_bits; i++)
		{
			int bit = Random::GenerateRealUniform() < bit_probability;
			symbol += bit * power;
			bits.emplace_back(bit);
			
			LOG_INFO("i = {}, bit = {}, symbol = {}", i, bit, symbol);
			power /= 2;
			
		}
		symbol_file.Write(bits);
	}

	void ActiveActorRandomBits::NextRealisation()
	{
		// base class resets
		SetEventTime(start_time);
		local_time = start_time;
		last_action_time = start_time;
		// derived class resets
		release_index = 0;
		symbol = 0;
		symbol_file.NewFile(CreateSymbolFilePath());
	}

	std::string ActiveActorRandomBits::CreateSymbolFilePath()
	{
		return Environment::GetRealisationPath() + "a" + std::to_string(GetID()) + "_b.bin";
	}
}