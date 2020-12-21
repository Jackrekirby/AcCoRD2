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
	class Subvolume2;
}

namespace accord
{
	// move to seperate header
	class PassiveActorShape
	{
	public:
		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		virtual bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const = 0;

		virtual bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const PassiveActorShape& shape);

	// make passive actor base class with derived classes of different shapes so the shape
	// does not have to be a unique pointer
	// will eventually need to add mesoscopic::subvolume to typed subvolumes

	class PassiveActor : public Event
	{
		class TypedSubvolumes
		{
		public:
			TypedSubvolumes(MoleculeID id);

			void Add(microscopic::Subvolume2* subvolume);

			MoleculeID id;
			std::vector<microscopic::Subvolume2*> subvolumes;
		};
	public:
		PassiveActor(RegionIDs region_ids, MoleculeIDs molecule_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		PassiveActor(MoleculeIDs molecule_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		Type GetType() const;

		ActiveActorID GetID() const;

		void NextRealisation();

		void Run();

		virtual const PassiveActorShape* const GetShape() const = 0;
	private:
		std::vector<OutputBinaryVectors<Vec3d>> position_files;
		std::vector<OutputBinarySingles<size_t>> count_files;
		std::vector<OutputBinarySingles<double>> time_files;

		std::vector<TypedSubvolumes> enveloped_subvolumes;
		std::vector<TypedSubvolumes> partial_subvolumes;
		ActiveActorID id;
		double time_step;
		double start_time;

		MoleculeIDs molecule_ids;
		bool record_positions;
		bool record_time;

		void AddMicroscopicSubvolumes(MoleculeIDs molecule_ids, RegionIDs region_ids);

		void ObserveEnvelopedMicroscopicSubvolumes(std::vector<size_t>& counts);

		void ObservePartialMicroscopicSubvolumes(std::vector<size_t>& counts);

	protected:
		void CreateFiles();

		void AddMicroscopicSubvolumesWhichAreInsideActor(MoleculeIDs molecule_ids);
	};
}