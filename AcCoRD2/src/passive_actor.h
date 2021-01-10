#pragma once
#include "pch.h"
#include "event5.h"
#include "output_binary_vectors.h"
#include "output_binary_singles.h"
#include "object_ids.h"
#include "vec3d.h"
#include "relation_box.h"
#include "generating_box.h"

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

	class PassiveActor : public Event5
	{
		class TypedMicroscopicSubvolumes
		{
		public:
			TypedMicroscopicSubvolumes(MoleculeID id);

			void Add(microscopic::Subvolume* subvolume);

			MoleculeID id;
			std::vector<microscopic::Subvolume*> subvolumes;
		};

		class PartialMesoscopicSubvolume
		{
		public:
			PartialMesoscopicSubvolume(mesoscopic::Subvolume* subvolume, shape::generating::Box box);

			double in_area_probability;
			shape::generating::Box box;
			mesoscopic::Subvolume* subvolume;
		};
	public:
		PassiveActor(MicroRegionIDs region_ids, MicroRegionIDs meso_region_ids, MoleculeIDs molecule_ids,
			double start_time, int priority, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		PassiveActor(MoleculeIDs molecule_ids,
			double start_time, int priority, double time_step,
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

		std::vector<TypedMicroscopicSubvolumes> enveloped_microscopic_subvolumes;
		std::vector<TypedMicroscopicSubvolumes> partial_microscopic_subvolumes;

		std::vector<mesoscopic::Subvolume*> enveloped_mesoscopic_subvolumes;
		std::vector<PartialMesoscopicSubvolume> partial_mesoscopic_subvolumes;
		// SHOULD BE PASSIVE ACTOR ID
		ActiveActorID id;
		double time_step;
		double start_time;

		MoleculeIDs molecule_ids;
		bool record_positions;
		bool record_time;

		void AddMicroscopicSubvolumes(MoleculeIDs molecule_ids, MicroRegionIDs region_ids);

		void ObserveEnvelopedMicroscopicSubvolumes(std::vector<size_t>& counts);

		void ObservePartialMicroscopicSubvolumes(std::vector<size_t>& counts);

		void AddMesoscopicSubvolumes(MicroRegionIDs region_ids);

		void ObserveEnvelopedMesoscopicSubvolumes(std::vector<size_t>& counts);

		void ObservePartialMesoscopicSubvolumes(std::vector<size_t>& counts);

	protected:
		void CreateFiles();

		void AddMicroscopicSubvolumesWhichAreInsideActor(MoleculeIDs molecule_ids);
	};
}