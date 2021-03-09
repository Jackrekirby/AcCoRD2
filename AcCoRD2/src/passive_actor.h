// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "event.h"
#include "output_binary_vectors.h"
#include "output_binary_singles.h"
#include "vec3d.h"
#include "relation_box.h"
#include "generating_box.h"

#include "mesoscopic_region_id.h"
#include "microscopic_region_id.h"
#include "passive_actor_id.h"
#include "molecule_id.h"
#include "passive_actor_shape.h"

namespace accord::microscopic
{
	class Subvolume;
}

namespace accord::mesoscopic
{
	class Subvolume;
}

namespace accord
{
	class PassiveActor : public Event
	{
		class TypedMicroscopicSubvolumes
		{
		public:
			TypedMicroscopicSubvolumes(MoleculeID id);

			void Add(microscopic::Subvolume* subvolume);

			MoleculeID id;
			std::vector<microscopic::Subvolume*> subvolumes;
		};
	public:
		PassiveActor(const MicroscopicRegionIDs& region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time);

		PassiveActor(const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time);

		std::string LogEvent() const;

		void NextRealisation();

		void Run();

		virtual const PassiveActorShape& GetShape() const = 0;
	private:
		std::vector<OutputBinaryVectors<Vec3d>> position_files;
		std::vector<OutputBinarySingles<int>> count_files;
		std::vector<OutputBinarySingles<double>> time_files;

		std::vector<TypedMicroscopicSubvolumes> enveloped_microscopic_subvolumes;
		std::vector<TypedMicroscopicSubvolumes> partial_microscopic_subvolumes;

		std::vector<mesoscopic::Subvolume*> enveloped_mesoscopic_subvolumes;
		std::vector<mesoscopic::Subvolume*> partial_mesoscopic_subvolumes;

		PassiveActorID id;
		double time_step;
		double start_time;

		MoleculeIDs molecule_ids;
		bool record_positions;
		bool record_time;

		void AddMicroscopicSubvolumes(const MoleculeIDs& molecule_ids, const MicroscopicRegionIDs& region_ids);

		void ObserveEnvelopedMicroscopicSubvolumes(std::vector<int>& counts);

		void ObservePartialMicroscopicSubvolumes(std::vector<int>& counts);

		void AddMesoscopicSubvolumes(const MesoscopicRegionIDs& region_ids);

		void ObserveEnvelopedMesoscopicSubvolumes(std::vector<int>& counts);

		void ObservePartialMesoscopicSubvolumes(std::vector<int>& counts);

	protected:
		void CreateFiles();

		void AddMicroscopicSubvolumesWhichAreInsideActor(const MoleculeIDs& molecule_ids);

		void AddMesoscopicSubvolumesWhichAreInsideActor();
	};
}