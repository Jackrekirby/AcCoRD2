#pragma once
#include "pch.h"
#include "event.h"
#include "environment.h"
#include "output_binary_vectors.h"
#include "output_binary_singles.h"

namespace accord
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	using RegionID = int;
	using RegionIDs = std::vector<int>;

	using ActiveActorID = int;
	using ActiveActorIDs = std::vector<int>;

	class PassiveActorShape
	{
	public:
		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		virtual bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const = 0;

		virtual bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const = 0;
	};
	class microscopic::Subvolume2;

	
	// make passive actor base class with derived classes of different shapes so the shape
	// does not have to be a unique pointer

	class PassiveActor : public Event
	{
		class TypedSubvolumes
		{
		public:
			TypedSubvolumes(MoleculeID id)
				: id(id)
			{

			}

			MoleculeID id;
			std::vector<microscopic::Subvolume2*> subvolumes;
		};
	public:
		PassiveActor(std::unique_ptr<PassiveActorShape> shape, MoleculeIDs molecule_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step, 
			ActiveActorID id)
			: Event(start_time, priority, event_queue), shape(std::move(shape)), id(id),
			time_step(time_step)
		{
			AddMicroscopicSubvolumesWhichAreInsideActor(molecule_ids);
			CreateFiles();
		}

		PassiveActor(RegionIDs region_ids, MoleculeIDs molecules_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step,
			ActiveActorID id)
			: Event(start_time, priority, event_queue), shape(std::move(shape)), id(id),
			time_step(time_step)
		{
			AddMicroscopicSubvolumes(molecules_ids, region_ids);
			CreateFiles();
		}

		Type GetType() const
		{
			return Event::Type::passive_actor;
		}

		EventID GetID() const
		{
			return id;
		}

		void Run()
		{
			ObserveEnvelopedMicroscopicSubvolumes();
			ObservePartialMicroscopicSubvolumes();
			UpdateTime(GetTime() + time_step);
		}
	private:
		std::vector<accord::OutputBinaryVectors<Vec3d>> position_files;
		std::vector<TypedSubvolumes> enveloped_subvolumes;
		std::vector<TypedSubvolumes> partial_subvolumes;
		std::unique_ptr<PassiveActorShape> shape;
		ActiveActorID id;
		double time_step;

		void CreateFiles()
		{
			int n = Environment::GetNumberOfMoleculeTypes();
			position_files.reserve(n);
			std::string file_path = Environment::GetFilePath() + "p" +
				std::to_string(id) + "_m";
			for (int i = 0; i < n; i++)
			{
				
				position_files.emplace_back(file_path + std::to_string(i) + "_p.bin");
			}
		}

		void AddMicroscopicSubvolumesWhichAreInsideActor(MoleculeIDs molecule_ids)
		{
			for (auto& id : molecule_ids)
			{
				for (auto& region : Environment::microscopic_regions)
				{
					for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
					{
						if (shape->IsSubvolumeInsideBorder(subvolume.GetBoundingBox()))
						{
							enveloped_subvolumes.emplace_back(&subvolume);
						}
						else if (shape->IsSubvolumeOverlappingBorder(subvolume.GetBoundingBox()))
						{
							partial_subvolumes.emplace_back(&subvolume);
						}
						// otherwise subvolume is not inside actor so is ignored
					}
				}
			}
		}

		void AddMicroscopicSubvolumes(MoleculeIDs molecule_ids, RegionIDs region_ids)
		{
			for (auto& id : molecule_ids)
			{
				for (auto& region_id : region_ids)
				{
					auto& region = Environment::microscopic_regions.at(region_id);
					for (auto& subvolume : region.GetGrid(id).GetSubvolumes())
					{
						enveloped_subvolumes.emplace_back(&subvolume);
					}
				}
			}
		}

		void ObserveEnvelopedMicroscopicSubvolumes()
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
				positions.empty();
				id++;
			}
		}

		void ObservePartialMicroscopicSubvolumes()
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
				positions.empty();
				id++;
			}
		}
	};
}