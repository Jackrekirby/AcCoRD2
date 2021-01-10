#pragma once
#include "mesoscopic_subvolume.h"
#include "subvolume_queue.h"
#include "event5.h"
#include "vec3i.h"

namespace accord
{
	struct Vec3d;
}

// once all subvolumes are confirmed then add reactions and events to the queue
// may need to seperate mesoscopic and microscopic region ids
namespace accord::mesoscopic
{
	class Region : public Event5
	{
	public:
		Region(const Vec3d& origin, double length, const Vec3i& n_subvolumes,
			std::vector<double> diffusion_coefficients, double start_time, int priority, RegionID id);

		void AddMolecule(MoleculeID id, const Vec3d& position);

		void AddSubvolumesToQueue();

		void LinkSiblingSubvolumes();

		void LinkSiblingSubvolumes(const Vec3i& i);

		Subvolume& GetSubvolume(Vec3i index);

		Subvolume* GetSubvolumeIfExists(const Vec3i& index);

		void CreateSubvolumes(const Vec3i& n_subvolumes, std::vector<double> diffusion_coefficients,
			double subvolume_length);

		void AddZerothOrderReaction(MoleculeIDs products, double reaction_rate);

		void AddFirstOrderReaction(MoleculeID reactant, MoleculeIDs products, double reaction_rate);

		void AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, MoleculeIDs products, double reaction_rate);

		// will delete subvolumes from the region in preparation for another mesoscopic or microscopic region to be placed inside
		void AddChild();

		void AddNeighbour();

		// returns the required dimensions of the replacement region to ensure correct neighbouring (avoid floating point error)
		shape::basic::Box RemoveInterior(const Vec3i& origin_subvolume, const Vec3i& n_subvolumes);

		Event5::Type GetType() const;

		EventID GetID() const;

		void Run();

		void Print()
		{
			for (auto& subvolume : subvolumes)
			{
				LOG_INFO("id = {}, time = {}", subvolume.GetID(), subvolume.GetTime());
			}
		}
	private:
		SubvolumeQueue subvolume_queue;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box;
		RegionID id;

		Vec3i n_subvolumes;
	};
}