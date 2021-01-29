#pragma once
#include "mesoscopic_subvolume.h"
#include "subvolume_queue.h"
#include "event.h"
#include "vec3i.h"
#include "mesoscopic_region_id.h"
#include "mesoscopic_region_shape.h"


#include "microscopic_low_priority_relative.h"
#include "microscopic_neighbour_relative.h"
#include "microscopic_high_priority_relative.h"

namespace accord
{
	struct Vec3d;
}

// once all subvolumes are confirmed then add reactions and events to the queue
// may need to seperate mesoscopic and microscopic region ids

namespace accord::mesoscopic
{
	class Region : public Event, public microscopic::HighPriorityRelative, public microscopic::LowPriorityRelative, public microscopic::NeighbourRelative
	{
	public:
		Region(const Vec3d& origin, double length, const Vec3i& n_subvolumes, const std::vector<double>& diffusion_coefficients, const std::vector<Vec3i>& removedSubvolumes, int priority, const MesoscopicRegionID& id);

		void AddMolecule(const MoleculeID& id, const Vec3d& position);

		void AddSubvolumesToQueue();

		void LinkSiblingSubvolumes();

		Subvolume& GetSubvolume(Vec3i index);

		std::vector<Subvolume>& GetSubvolumes();

		Subvolume* GetSubvolumeIfExists(const Vec3i& index);

		int GetIndex(Vec3i index);

		void CreateSubvolumes(const Vec3i& n_subvolumes, std::vector<double> diffusion_coefficients,
			double subvolume_length, const std::vector<int>& removed_indices);

		void AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate);

		void AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate);

		void AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b, const std::vector<int>& products, double reaction_rate);

		// will delete subvolumes from the region in preparation for another mesoscopic or microscopic region to be placed inside
		void AddChild();

		void AddNeighbour(Region& region);

		// returns the required dimensions of the replacement region to ensure correct neighbouring (avoid floating point error)
		shape::basic::Box RemoveInterior(const Vec3i& origin_subvolume, const Vec3i& n_subvolumes);

		std::string LogEvent() const;

		void Run();

		void Print();

		const shape::relation::Box& GetBoundingBox() const;

		void ToJson(Json& j) const;

		void RefreshEventTime();

		void NextRealisation();

		MesoscopicRegionID GetID() const;
		

		// hybrid functions

		const RegionShape& GetShape() const;

		const SurfaceDirection& GetSurfaceDirection() const;

		bool IsRegion() const;

		std::optional<microscopic::MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, microscopic::Grid* owner,
			microscopic::SurfaceType surface_type, int cycles, bool allowObstructions);

	private:
		SubvolumeQueue subvolume_queue;
		std::vector<Subvolume> subvolumes;
		RegionShape box;
		MesoscopicRegionID id;
		Vec3i n_subvolumes;
		double subvolume_length;

		// hybrid variables
		microscopic::HighPriorityRelative::SurfaceDirection surface_direction;
	};

	void to_json(Json& j, const Region& region);
}