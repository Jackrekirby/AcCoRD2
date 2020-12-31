#include "pch.h"
#include "active_actor_non_random.h"

namespace accord
{
	ActiveActorNonRandom::ActiveActorNonRandom(double action_interval, double release_interval, double slot_interval,
		std::vector<int> bit_sequence, double n_modulation_bits, std::string file_path,
		MoleculeIDs release_molecules, int modulation_strength, std::vector<microscopic::Region*> regions,
		std::unique_ptr<ActiveActorShape> shape,
		double start_time, int priority, EventQueue* event_queue, ActiveActorID id)
		: ActiveActor2(action_interval, release_interval, release_molecules, modulation_strength, regions, std::move(shape),
			start_time, priority, event_queue, id), n_modulation_bits(n_modulation_bits), bit_sequence(bit_sequence),
			slot_interval(slot_interval), symbol(0), symbol_index(0), n_releases_per_interval(release_interval / slot_interval),
		release_index(release_index)
	{
		LOG_INFO("action = {}, release = {}, slot = {}", action_interval, release_interval, slot_interval);

		OutputBinaryVectors<int> symbol_file(file_path);
		symbol_file.Write(bit_sequence);
		GenerateSymbol();
	}

	void ActiveActorNonRandom::Run()
	{
		ReleaseMolecules(symbol * modulation_strength);
		if (SetNextReleaseTime(slot_interval))
		{
			GenerateSymbol();
		}
	};

	void ActiveActorNonRandom::GenerateSymbol()
	{
		symbol = 0;
		int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
		auto end = bit_sequence.begin() + symbol_index + n_modulation_bits;
		for (auto bit = bit_sequence.begin() + symbol_index; bit != end; ++bit)
		{
			symbol += *bit * power;
			//LOG_INFO("bit = {}, symbol = {}", *bit, symbol);
			power /= 2;
		}
		symbol_index += n_modulation_bits;
	}


	// return true if a new symbol needs to be generated
	bool ActiveActorNonRandom::SetNextReleaseTime(double elapsed_time)
	{
		LOG_INFO("local time = {}, last_action_time = {}, elapsed_time = {}, delta = {}", local_time, last_action_time, elapsed_time, local_time - last_action_time);
		local_time += elapsed_time; // or random time
		if (local_time - last_action_time < release_interval)
		{
			//LOG_INFO("time still within release time {}", local_time);
			// time still within release interval
			UpdateTime(local_time);
			return false;
		}
		else // local_time - last_action_time >= release_interval
		{
			// release interval passed so must wait until next action interval
			//LOG_INFO("wait until next action interval", local_time);
			last_action_time += action_interval;
			local_time = last_action_time;
			UpdateTime(local_time);
			return true;
		}
	}
}