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
	private:
		SubvolumeQueue subvolume_queue;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box;
	};
}