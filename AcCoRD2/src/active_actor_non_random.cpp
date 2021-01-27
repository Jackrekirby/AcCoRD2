#include "pch.h"
#include "active_actor_non_random.h"
#include "environment.h"

namespace accord
{
	ActiveActorNonRandom::ActiveActorNonRandom(double action_interval, double release_interval, double slot_interval,
		const std::vector<int>& bit_sequence, int n_modulation_bits,
		const std::vector<int>& release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& micro_regions,
		const std::vector<mesoscopic::Region*>& meso_regions, std::unique_ptr<ActiveActorShape> shape,
		double start_time, int priority, const ActiveActorID& id)
		: ActiveActor(action_interval, release_interval, release_molecules, modulation_strength, micro_regions, meso_regions, std::move(shape),
			start_time, priority, id), n_modulation_bits(n_modulation_bits), bit_sequence(bit_sequence),
			slot_interval(slot_interval), symbol(0), symbol_index(0),
			n_releases_per_interval(static_cast<int>(release_interval / slot_interval)), release_index(0)
	{
		LOG_INFO("action = {}, release = {}, slot = {}", action_interval, release_interval, slot_interval);

		OutputBinaryVectors<int> symbol_file(CreateSymbolFilePath());
		symbol_file.Write(bit_sequence);
	}

	void ActiveActorNonRandom::Run()
	{
		if (release_index == 0)
		{
			if (symbol_index >= bit_sequence.size())
			{
				LOG_INFO("no more symbols");
				// if there are no more bits left that set its next event to after the end of the simulation
				// could add max number of event executions
				SetEventTime(Environment::GetRunTime() + 1);
				return;
			}
			else
			{
				GenerateSymbol();
			}
		}
		
		if (release_index < n_releases_per_interval)
		{
			LOG_INFO("Releasing Molecule {}", symbol * modulation_strength);
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

	void ActiveActorNonRandom::GenerateSymbol()
	{
		symbol = 0;
		int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
		auto end = bit_sequence.begin() + symbol_index + n_modulation_bits;
		for (auto bit = bit_sequence.begin() + symbol_index; bit != end; ++bit)
		{
			symbol += *bit * power;
			LOG_INFO("bit = {}, symbol = {}", *bit, symbol);
			power /= 2;
		}
		LOG_INFO("symbol_index = {}", symbol_index);
		symbol_index += n_modulation_bits;
	}

	std::string ActiveActorNonRandom::CreateSymbolFilePath()
	{
		return Environment::GetRealisationPath() + "a" + std::to_string(GetID()) + "_b.bin";
	}

	void ActiveActorNonRandom::NextRealisation()
	{
		// base class resets
		SetEventTime(start_time);
		local_time = start_time;
		last_action_time = start_time;
		// derived class resets
		release_index = 0;
		symbol = 0;
		symbol_index = 0;
		// write bit sequence to realisation folder
		OutputBinaryVectors<int> symbol_file(CreateSymbolFilePath());
		symbol_file.Write(bit_sequence);
	}
}