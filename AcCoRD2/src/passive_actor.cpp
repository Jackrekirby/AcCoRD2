#include "pch.h"
#include "passive_actor.h"
#include "microscopic_subvolume2.h"
#include "environment.h"

namespace accord
{
	// make passive actor base class with derived classes of different shapes so the shape
	// does not have to be a unique pointer

	// nested class may not work
	// can all typed subvolumes be merged into single class?
	// consider renaming to SubvolumeVector
	PassiveActor::TypedSubvolumes::TypedSubvolumes(MoleculeID id)
		: id(id)
	{

	}

	void PassiveActor::TypedSubvolumes::Add(microscopic::Subvolume2* subvolume)
	{
		subvolumes.emplace_back(subvolume);
	}

	PassiveActor::PassiveActor(std::unique_ptr<PassiveActorShape> shape, MoleculeIDs molecule_ids,
		double start_time, int priority, EventQueue* event_queue, double time_step,
		ActiveActorID id, bool record_positions, bool record_time)
		: Event(start_time, priority, event_queue), shape(std::move(shape)), id(id),
		time_step(time_step), record_positions(record_positions), record_time(record_time),
		molecule_ids(molecule_ids)
	{
		AddMicroscopicSubvolumesWhichAreInsideActor(molecule_ids);
		CreateFiles();
	}

	PassiveActor::PassiveActor(RegionIDs region_ids, MoleculeIDs molecule_ids,
		double start_time, int priority, EventQueue* event_queue, double time_step,
		ActiveActorID id, bool record_positions, bool record_time)
		: Event(start_time, priority, event_queue), shape(std::move(shape)), id(id),
		time_step(time_step), record_positions(record_positions), record_time(record_time),
		molecule_ids(molecule_ids)
	{
		AddMicroscopicSubvolumes(molecule_ids, region_ids);
		CreateFiles();
	}

	Event::Type PassiveActor::GetType() const
	{
		return Event::Type::passive_actor;
	}

	ActiveActorID PassiveActor::GetID() const
	{
		return id;
	}

	void PassiveActor::NextRealisation()
	{
		for (auto& position_file : position_files)
		{
			position_file.Close();
		}
		for (auto& count_file : count_files)
		{
			count_file.Close();
		}
		time_file->Close();

		position_files.clear();
		count_files.clear();
		time_file = nullptr;

		CreateFiles();
	}

	void PassiveActor::Run()
	{
		if (record_time) time_file->Write(GetTime());
		ObserveEnvelopedMicroscopicSubvolumes();
		ObservePartialMicroscopicSubvolumes();
		UpdateTime(GetTime() + time_step);
	}

	void PassiveActor::CreateFiles()
	{
		int n = Environment::GetNumberOfMoleculeTypes();
		position_files.reserve(n);

		if (record_time)
		{
			time_file = std::make_unique<OutputBinarySingles<double>>(Environment::GetFilePath() + "p" + std::to_string(id) + "_t.bin");
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

	void PassiveActor::AddMicroscopicSubvolumesWhichAreInsideActor(MoleculeIDs molecule_ids)
	{
		for (auto& id : molecule_ids)
		{
			enveloped_subvolumes.emplace_back(id);
			partial_subvolumes.emplace_back(id);
			for (auto& region : Environment::microscopic_regions)
			{
				for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
				{
					if (shape->IsSubvolumeInsideBorder(subvolume.GetBoundingBox()))
					{
						enveloped_subvolumes.back().Add(&subvolume);
					}
					else if (shape->IsSubvolumeOverlappingBorder(subvolume.GetBoundingBox()))
					{
						partial_subvolumes.back().Add(&subvolume);
					}
					// otherwise subvolume is not inside actor so is ignored
				}
			}
		}
	}

	void PassiveActor::AddMicroscopicSubvolumes(MoleculeIDs molecule_ids, RegionIDs region_ids)
	{
		for (auto& id : molecule_ids)
		{
			enveloped_subvolumes.emplace_back(id);
			for (auto& region_id : region_ids)
			{
				auto& region = Environment::microscopic_regions.at(region_id);
				for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
				{
					enveloped_subvolumes.back().Add(&subvolume);
				}
			}
		}
	}

	void PassiveActor::ObserveEnvelopedMicroscopicSubvolumes()
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
					positions.emplace_back(molecule.GetPosition());
				}

				for (auto& molecule : subvolume->GetRecentMolecules())
				{
					positions.emplace_back(molecule.GetPosition());
				}
			}
			// write positions all of the same molecule type to file
			position_files.at(id).Write(positions);
			count_files.at(id).Write(positions.size());
			positions.clear();
			id++;
		}
	}

	void PassiveActor::ObservePartialMicroscopicSubvolumes()
	{
		MoleculeID id = 0;
		// get all partial subvolumes of a given type
		for (auto& typed_subvolumes : partial_subvolumes)
		{
			std::vector<Vec3d> positions;
			// iterate through each subvolume all of the same type and get positions
			for (auto& subvolume : typed_subvolumes.subvolumes)
			{
				for (auto& molecule : subvolume->GetNormalMolecules())
				{
					// check if each molecule is inside the shape
					if (shape->IsMoleculeInsideBorder(molecule.GetPosition()))
					{
						positions.emplace_back(molecule.GetPosition());
					}
				}

				for (auto& molecule : subvolume->GetRecentMolecules())
				{
					// check if each molecule is inside the shape
					if (shape->IsMoleculeInsideBorder(molecule.GetPosition()))
					{
						positions.emplace_back(molecule.GetPosition());
					}
				}
			}
			// write positions all of the same molecule type to file
			position_files.at(id).Write(positions);
			count_files.at(id).Write(positions.size());
			positions.clear();
			id++;
		}
	}
}