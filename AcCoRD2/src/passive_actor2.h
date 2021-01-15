#pragma once
#include "pch.h"
#include "event.h"
#include "output_binary_vectors.h"
#include "output_binary_singles.h"
#include "object_ids.h"
#include "vec3d.h"
#include "relation_box.h"

namespace accord::microscopic
{
	class Subvolume;
}

namespace accord
{
	class PassiveActor2 : public Event
	{
		class TypedSubvolumes
		{
		public:
			TypedSubvolumes(const MoleculeID& id);

			void Add(microscopic::Subvolume* subvolume);

			MoleculeID id;
			std::vector<microscopic::Subvolume*> subvolumes;
		};
	public:
		PassiveActor2(const MicroscopicRegionIDs& microscopic_region_ids, const MoleculeIDs& molecule_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		Type GetType() const;

		const PassiveActorID& GetID() const;

		void NextRealisation();

		void Run();
	private:
		std::vector<OutputBinaryVectors<Vec3d>> position_files;
		std::vector<OutputBinarySingles<size_t>> count_files;
		std::vector<OutputBinarySingles<double>> time_files;
		std::vector<TypedSubvolumes> enveloped_subvolumes;

		MoleculeIDs molecule_ids;
		ActiveActorID id;
		double time_step;
		double start_time;
		bool record_positions;
		bool record_time;

		void CreateFiles();

		void AddMicroscopicSubvolumes(const MoleculeIDs& molecule_ids, const MicroscopicRegionIDs& microscopic_region_ids);

		void ObserveEnvelopedMicroscopicSubvolumes();

	};
}