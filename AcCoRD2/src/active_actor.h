#pragma once
#include "pch.h"
#include "event.h"
#include "output_binary_vectors.h"
#include "object_ids.h"

namespace accord
{
	class ActiveActor : public Event
	{
	public:
		ActiveActor(double action_interval, double release_interval, double slot_interval,
			int n_modulation_bits, double bit_probability, std::vector<int> bit_sequence,
			MoleculeIDs release_molecules,
			double start_time, int priority, EventQueue* event_queue, std::string file_path)
			: action_interval(action_interval), release_interval(release_interval),
			slot_interval(slot_interval), Event(start_time, priority, event_queue),
			local_time(start_time), last_action_time(start_time), symbol_file(file_path),
			n_modulation_bits(n_modulation_bits), bit_probability(bit_probability),
			bit_sequence(bit_sequence), release_molecules(release_molecules)
		{

		}
		void Run()
		{
			// ReleaseMolecules()
			// SetNextReleaseTime()
		}

		Type GetType() const
		{
			return Type::active_actor;
		}

		EventID GetID() const
		{
			return id;
		}

		void ReleaseMolecules()
		{
			// for non random release time


			// for random release time


		}

		void SetNextReleaseTime()
		{
			local_time += slot_interval; // or random time
			if (local_time - last_action_time < release_interval)
			{
				// time still within release interval
				UpdateTime(local_time);
			}
			else // local_time - last_action_time >= release_interval
			{
				// release interval passed so must wait until next action interval
				last_action_time += release_interval;
				UpdateTime(last_action_time);
				// calculate symbol
			}
		}

		void GetSymbolFromBitSequence()
		{
			modulation_stength = 0;
			int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
			auto end = bit_sequence.begin() + symbol_index + n_modulation_bits;
			for (auto bit = bit_sequence.begin() + symbol_index; bit != end; ++bit)
			{
				modulation_stength += *bit * power;
				LOG_INFO("bit = {}, modulation strength = {}", *bit, modulation_stength);
				power /= 2;
			}
			symbol_index += n_modulation_bits;
		}

		void GenerateRandomBits()
		{
			std::vector<int> bits; 
			bits.reserve(n_modulation_bits);
			symbol = 0;
			int power = static_cast<int>(std::pow(2, n_modulation_bits - 1));
			for (int i = 0; i < n_modulation_bits; i++)
			{
				int bit = (Random::GenerateRealUniform() < bit_probability);
				symbol += bit * power;
				LOG_INFO("bit = {}, symbol = {}", bit, symbol);
				power /= 2;
				bits.emplace_back(bit);
			}
			symbol_file.Write(bits);
		}

	private:
		double local_time;
		double action_interval;
		double last_action_time;
		double release_interval;
		double slot_interval;

		int modulation_stength;
		int symbol;
		int symbol_index;
		double bit_probability;
		int n_modulation_bits;

		MoleculeIDs release_molecules;

		ActiveActorID id;

		std::vector<int> bit_sequence;

		OutputBinaryVectors<int> symbol_file;
	};
}