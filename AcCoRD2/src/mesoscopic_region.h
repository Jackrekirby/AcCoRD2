#pragma once
#include "mesoscopic_subvolume.h"
#include "subvolume_queue.h"

namespace accord
{
	struct Vec3i;
	struct Vec3d;
}

namespace accord::mesoscopic
{
	class Region
	{
	public:
		Region(const Vec3d& origin, double length, const Vec3i& n_subvolumes,
			std::vector<double> diffusion_coefficients);

		void AddSubvolumesToQueue();

		void CreateSubvolumes(const Vec3i& n_subvolumes, std::vector<double> diffusion_coefficients,
			double subvolume_length);

		void AddZerothOrderReaction(MoleculeIDs products, double reaction_rate);

		void AddFirstOrderReaction(MoleculeID reactant, MoleculeIDs products, double reaction_rate);

		void AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, MoleculeIDs products, double reaction_rate);

		// will delete subvolumes from the region in preparation for another mesoscopic or microscopic region to be placed inside
		void AddChild()
		{
			// for both meso and microscopic regions
			// check for intersection with each subvolume and delete those which intersect
			// for those which neighbour add as neighbour (just send across to the add neighbour function
		}

		void AddNeighbour()
		{
			// for those which neighbour add as neighbour
		}

		// returns the required dimensions of the replacement region to ensure correct neighbouring (avoid floating point error)
		shape::basic::Box RemoveInterior(const Vec3i& origin_subvolume, const Vec3i& n_subvolumes)
		{
			return { box.GetOrigin() + box.GetLength() * origin_subvolume, 
				box.GetOrigin() + box.GetLength() * (origin_subvolume + n_subvolumes) };
		}
	private:
		SubvolumeQueue subvolume_queue;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box;
	};
}