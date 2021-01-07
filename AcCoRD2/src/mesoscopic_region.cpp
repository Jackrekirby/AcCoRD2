#include "pch.h"
#include "mesoscopic_region.h"
#include "vec3d.h"
#include "vec3i.h"

namespace accord::mesoscopic
{
	Region::Region(const Vec3d& origin, double subvolume_length, const Vec3i& n_subvolumes, 
		std::vector<double> diffusion_coefficients)
		: box(origin, subvolume_length * Vec3d(n_subvolumes))
	{
		CreateSubvolumes(n_subvolumes, diffusion_coefficients, subvolume_length);
	}

	void Region::AddSubvolumesToQueue()
	{
		subvolume_queue.Reserve(subvolumes.size());
		for (auto& subvolume : subvolumes)
		{
			subvolume_queue.Add(&subvolume);
		}
	}

	void Region::CreateSubvolumes(const Vec3i& n_subvolumes, 
		std::vector<double> diffusion_coefficients, double subvolume_length)
	{
		subvolumes.reserve(n_subvolumes.Volume());
		Vec3i i;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					subvolumes.emplace_back(box.GetOrigin() + Vec3d(i) * subvolume_length, 
						subvolume_length, diffusion_coefficients);
				}
			}
		}
	}
}