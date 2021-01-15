#include "pch.h"
#include "passive_actor2.h"
#include "microscopic_subvolume2.h"
#include "environment.h"

namespace accord
{
	PassiveActor2::TypedSubvolumes::TypedSubvolumes(MoleculeID id)
		: id(id)
	{

	}

	void PassiveActor2::TypedSubvolumes::Add(microscopic::Subvolume2* subvolume)
	{
		subvolumes.emplace_back(subvolume);
	}

	PassiveActor2::PassiveActor2(RegionIDs region_ids, MoleculeIDs molecule_ids,
		double start_time, int priority, EventQueue* event_queue, double time_step,
		ActiveActorID id, bool record_positions, bool record_time)
		: Event(start_time, priority, event_queue), id(id),
		time_step(time_step), record_positions(record_positions), record_time(record_time),
		molecule_ids(molecule_ids), start_time(start_time)
	{
		AddMicroscopicSubvolumes(molecule_ids, region_ids);
		CreateFiles();
	}

	Event::Type PassiveActor2::GetType() const
	{
		return Event::Type::passive_actor;
	}

	ActiveActorID PassiveActor2::GetID() const
	{
		return id;
	}

	void PassiveActor2::NextRealisation()
	{
		for (auto& position_file : position_files)
		{
			position_file.Close();
		}
		for (auto& count_file : count_files)
		{
			count_file.Close();
		}
		for (auto& time_file : time_files)
		{
			time_file.Close();
		}

		position_files.clear();
		count_files.clear();
		time_files.clear();

		CreateFiles();

		UpdateTime(start_time);
	}

	void PassiveActor2::Run()
	{
		if (record_time) time_files.begin()->Write(GetTime());
		ObserveEnvelopedMicroscopicSubvolumes();
		UpdateTime(GetTime() + time_step);
	}

	void PassiveActor2::CreateFiles()
	{
		int n = Environment::GetNumberOfMoleculeTypes();
		position_files.reserve(n);

		if (record_time)
		{
			time_files.emplace_back(Environment::GetFilePath() + "p" + std::to_string(id) + "_t.bin");
		}

		std::string file_path = Environment::GetFilePath() + "p" +
			std::to_string(id) + "_m";
		for (auto& id : molecule_ids)
		{
			if (record_positions)
			{
				position_files.emplace_back(file_path + std::to_string(id) + "_p.bin");
			}
			count_files.emplace_back(file_path + std::to_string(id) + "_c.bin");
		}
	}

	void PassiveActor2::AddMicroscopicSubvolumes(MoleculeIDs molecule_ids, RegionIDs region_ids)
	{
		for (auto& id : molecule_ids)
		{
			enveloped_subvolumes.emplace_back(id);
			for (auto& region_id : region_ids)
			{
				auto& region = Environment::GetRegion(region_id);
				for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
				{
					enveloped_subvolumes.back().Add(&subvolume);
				}
			}
		}
	}

	void PassiveActor2::ObserveEnvelopedMicroscopicSubvolumes()
	{
		MoleculeID id = 0;
		// get all enveloped subvolumes of a given type
		for (auto& typed_subvolumes : enveloped_subvolumes)
		{
			std::vector<Vec3d> positions;
			// iterate through each subvolume all of the same type and get positions
			for (auto& subvolume : typed_subvolumes.subvolumes)
			{
				for (auto& molecule : subvolume->GetNormalMolecules())
				{
					//LOG_ERROR(molecule.GetPosition());
					positions.emplace_back(molecule.GetPosition());
				}

				for (auto& molecule : subvolume->GetRecentMolecules())
				{
					//LOG_WARN(molecule.GetPosition());
					positions.emplace_back(molecule.GetPosition());
				}
			}
			// write positions all of the same molecule type to file
			if (positions.size() != 0)
			{

				position_files.at(id).Write(positions);
			}
			count_files.at(id).Write(positions.size());
			positions.clear();
			id++;
		}
	}

}