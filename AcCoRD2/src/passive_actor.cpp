// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "passive_actor.h"
#include "microscopic_subvolume.h"
#include "environment.h"
#include "mesoscopic_subvolume.h"
#include "passive_actor_shape.h"

namespace accord
{
	// make passive actor base class with derived classes of different shapes so the shape
	// does not have to be a unique pointer

	// nested class may not work
	// can all typed subvolumes be merged into single class?
	// consider renaming to SubvolumeVector
	PassiveActor::TypedMicroscopicSubvolumes::TypedMicroscopicSubvolumes(MoleculeID id)
		: id(id)
	{

	}

	void PassiveActor::TypedMicroscopicSubvolumes::Add(microscopic::Subvolume* subvolume)
	{
		subvolumes.emplace_back(subvolume);
	}

	PassiveActor::PassiveActor(const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step,
		const PassiveActorID& id, bool record_positions, bool record_time)
		: Event(start_time, priority), id(id), time_step(time_step), record_positions(record_positions), record_time(record_time),
		molecule_ids(molecule_ids), start_time(start_time)
	{
		
	}

	PassiveActor::PassiveActor(const MicroscopicRegionIDs& microscopic_region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time)
		: Event(start_time, priority), id(id),
		time_step(time_step), record_positions(record_positions), record_time(record_time),
		molecule_ids(molecule_ids), start_time(start_time)
	{
		AddMicroscopicSubvolumes(molecule_ids, microscopic_region_ids);
		AddMesoscopicSubvolumes(mesoscopic_region_ids);
		CreateFiles();
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
		for (auto& time_file : time_files)
		{
			time_file.Close();
		}

		position_files.clear();
		count_files.clear();
		time_files.clear();

		CreateFiles();

		SetEventTime(start_time);
	}

	void PassiveActor::Run()
	{
		if (record_time) time_files.begin()->Write(GetEventTime());
		std::vector<int> counts(molecule_ids.size(), 0);
		ObserveEnvelopedMicroscopicSubvolumes(counts);
		ObservePartialMicroscopicSubvolumes(counts);

		ObserveEnvelopedMesoscopicSubvolumes(counts);
		ObservePartialMesoscopicSubvolumes(counts);

		int i = 0;
		for (auto& count : counts)
		{
			//LOG_INFO("{}", count);
			count_files.at(i).Write(count);
			i++;
		}
		UpdateEventTime(time_step);
	}

	void PassiveActor::CreateFiles()
	{
		int n = Environment::GetNumberOfMoleculeTypes();
		position_files.reserve(n);

		if (record_time)
		{
			time_files.emplace_back(Environment::GetRealisationPath() + "p" + std::to_string(id) + "_t.bin");
		}

		std::string file_path = Environment::GetRealisationPath() + "p" +
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

	void PassiveActor::AddMicroscopicSubvolumesWhichAreInsideActor(const MoleculeIDs& molecule_ids)
	{
		for (auto& id : molecule_ids)
		{
			enveloped_microscopic_subvolumes.emplace_back(id);
			partial_microscopic_subvolumes.emplace_back(id);
			for (auto& region : Environment::GetRegions())
			{
				//LOG_INFO(region->GetID());
				for (auto& subvolume : region->GetGrid(id).GetSubvolumes())
				{
					if (GetShape().IsSubvolumeInsideBorder(subvolume.GetBoundingBox()))
					{
						//LOG_INFO("enveloped");
						enveloped_microscopic_subvolumes.back().Add(&subvolume);
					}
					else if (GetShape().IsSubvolumeOverlappingBorder(subvolume.GetBoundingBox()))
					{
						//LOG_INFO("partial");
						partial_microscopic_subvolumes.back().Add(&subvolume);
					}
					// otherwise subvolume is not inside actor so is ignored
				}
			}
		}
	}

	void PassiveActor::AddMesoscopicSubvolumesWhichAreInsideActor()
	{
		for (auto& region : Environment::GetMesoscopicRegions())
		{
			for (auto& subvolume : region.GetSubvolumes())
			{
				if (GetShape().IsSubvolumeInsideBorder(subvolume.GetBoundingBox()))
				{
					//LOG_INFO("adding enveloped subvolume");
					enveloped_mesoscopic_subvolumes.emplace_back(&subvolume);
				}
				else if (GetShape().IsSubvolumeOverlappingBorder(subvolume.GetBoundingBox()))
				{
					// cannot generate overlap box if actor shape is not a box.
					// therefore will have to resort to genrating position then checking if it is within the actor
					//subvolume.GetBoundingBox().GenerateOverlapBox();
					//LOG_INFO("Adding partial subvolume");
					partial_mesoscopic_subvolumes.emplace_back(&subvolume);
				}
				// otherwise subvolume is not inside actor so is ignored
			}
		}
		
	}

	void PassiveActor::AddMicroscopicSubvolumes(const MoleculeIDs& molecule_ids, const MicroscopicRegionIDs& region_ids)
	{
		for (auto& id : molecule_ids)
		{
			enveloped_microscopic_subvolumes.emplace_back(id);
			for (auto& region_id : region_ids)
			{
				auto& region = Environment::GetMicroscopicRegion(region_id);
				for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
				{
					enveloped_microscopic_subvolumes.back().Add(&subvolume);
				}
			}
		}
	}

	void PassiveActor::AddMesoscopicSubvolumes(const MesoscopicRegionIDs& region_ids)
	{
		for (auto& region : Environment::GetMesoscopicRegions(region_ids))
		{
			for (auto& subvolume : region->GetSubvolumes())
			{
				enveloped_mesoscopic_subvolumes.emplace_back(&subvolume);
			}
		}
	}

	void PassiveActor::ObserveEnvelopedMicroscopicSubvolumes(std::vector<int>& counts)
	{
		int i = 0;
		// get all enveloped subvolumes of a given type
		if (record_positions)
		{
			for (auto& typed_subvolumes : enveloped_microscopic_subvolumes)
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
					position_files.at(i).Write(positions);
				}
				//LOG_INFO("{} {} {}", counts.at(id), positions.size(), static_cast<int>(positions.size()));
				counts.at(i) += static_cast<int>(positions.size());
				//LOG_INFO("{} {} {}", counts.at(id), positions.size(), static_cast<int>(positions.size()));
				positions.clear();
				i++;
			}
		}
		else
		{
			for (auto& typed_subvolumes : enveloped_microscopic_subvolumes)
			{
				auto& count = counts.at(i);
				for (auto& subvolume : typed_subvolumes.subvolumes)
				{
					for (auto& molecule : subvolume->GetNormalMolecules())
					{
						++count;
					}
					for (auto& molecule : subvolume->GetRecentMolecules())
					{
						++count;
					}
				}
				i++;
			}
		}
	}

	void PassiveActor::ObservePartialMicroscopicSubvolumes(std::vector<int>& counts)
	{
		int i = 0;
		// get all partial subvolumes of a given type
		if (record_positions)
		{
			for (auto& typed_subvolumes : partial_microscopic_subvolumes)
			{
				std::vector<Vec3d> positions;
				// iterate through each subvolume all of the same type and get positions
				for (auto& subvolume : typed_subvolumes.subvolumes)
				{
					for (auto& molecule : subvolume->GetNormalMolecules())
					{
						// check if each molecule is inside the shape
						if (GetShape().IsMoleculeInsideBorder(molecule.GetPosition()))
						{
							positions.emplace_back(molecule.GetPosition());
						}
					}

					for (auto& molecule : subvolume->GetRecentMolecules())
					{
						// check if each molecule is inside the shape
						if (GetShape().IsMoleculeInsideBorder(molecule.GetPosition()))
						{
							positions.emplace_back(molecule.GetPosition());
						}
					}
				}
				// write positions all of the same molecule type to file
				if (positions.size() != 0)
				{
					position_files.at(i).Write(positions);
				}
				counts.at(i) += static_cast<int>(positions.size());
				positions.clear();
				i++;
			}
		}
		else
		{
			for (auto& typed_subvolumes : partial_microscopic_subvolumes)
			{
				auto& count = counts.at(i);
				// iterate through each subvolume all of the same type and get counts
				for (auto& subvolume : typed_subvolumes.subvolumes)
				{
					for (auto& molecule : subvolume->GetNormalMolecules())
					{
						// check if each molecule is inside the shape
						if (GetShape().IsMoleculeInsideBorder(molecule.GetPosition()))
						{
							++count;
						}
					}

					for (auto& molecule : subvolume->GetRecentMolecules())
					{
						// check if each molecule is inside the shape
						if (GetShape().IsMoleculeInsideBorder(molecule.GetPosition()))
						{
							++count;
						}
					}
				}
				i++;
			}
		}
	}

	void PassiveActor::ObserveEnvelopedMesoscopicSubvolumes(std::vector<int>& counts)
	{
		int i = 0;
		if (record_positions)
		{
			for (MoleculeID id : molecule_ids)
			{
				std::vector<Vec3d> positions;
				for (auto& subvolume : enveloped_mesoscopic_subvolumes)
				{
					auto& box = subvolume->GetBoundingBox();
					size_t count = subvolume->GetLayer(id).GetCount();
					positions.reserve(positions.size() + count);
					for (size_t j = 0; j < count; j++)
					{
						positions.emplace_back(box.GeneratePointInVolume());
					}
				}
				// write positions all of the same molecule type to file
				if (positions.size() != 0)
				{
					position_files.at(i).Write(positions);
				}
				counts.at(i) += static_cast<int>(positions.size());
				positions.clear();
				i++;
			}
		}
		else
		{
			for (MoleculeID id : molecule_ids)
			{
				auto& count = counts.at(i);
				for (auto& subvolume : enveloped_mesoscopic_subvolumes)
				{
					count += subvolume->GetLayer(id).GetCount();
				}
				i++;
			}
		}

	}

	void PassiveActor::ObservePartialMesoscopicSubvolumes(std::vector<int>& counts)
	{
		int i = 0;
		if (record_positions)
		{
			for (MoleculeID id : molecule_ids)
			{
				std::vector<Vec3d> positions;
				for (auto& partial_subvolume : partial_mesoscopic_subvolumes)
				{
					size_t count = partial_subvolume->GetLayer(id).GetCount();
					//double probability = partial_subvolume.in_area_probability;
					// in order to not generate a random number per molecule in the subvolume to determine if the molecule is inside the
					// partial subvolume a single random number can be generated to determine the total number of molecules inside the
					// parital subvolume.
					//int count_in_partial_subvolume = static_cast<int>(std::round(count * ((Random::GenerateRealUniform() - probability) / probability)));
					//
					for (int j = 0; j < count; j++)
					{
						Vec3d position = partial_subvolume->GetBoundingBox().GeneratePointInVolume();
						if (GetShape().IsMoleculeInsideBorder(position))
						{
							positions.emplace_back(position);
						}
					}
				}
				// write positions all of the same molecule type to file
				if (positions.size() != 0)
				{
					position_files.at(i).Write(positions);
				}
				counts.at(i) += static_cast<int>(positions.size());
				positions.clear();
				i++;
			}
		}
		else
		{
			for (MoleculeID id : molecule_ids)
			{
				auto& count = counts.at(i);
				for (auto& partial_subvolume : partial_mesoscopic_subvolumes)
				{
					size_t subvolume_count = partial_subvolume->GetLayer(id).GetCount();
					for (int j = 0; j < subvolume_count; j++)
					{
						if (GetShape().IsMoleculeInsideBorder(partial_subvolume->GetBoundingBox().GeneratePointInVolume()))
						{
							++count;
						}
					}
				}
				i++;
			}
		}
	}

	std::string PassiveActor::LogEvent() const
	{
		return fmt::format("Passive Actor. ID:{}, Priority:{}, Time:{}", id, priority, time);
	}
}