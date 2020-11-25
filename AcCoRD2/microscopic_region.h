#pragma once
#include "pch.h"
#include "relation_box.h"
#include "collision_box.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	using OptionalCollision3D = std::optional<shape::collision::Collision3D>;
	using ID = int;

	class Box : public shape::relation::Box, public shape::collision::Box, public RegionShape
	{
	public:
		// can foresee multiple inheritance problem
		// make inheritance virtual ?
		// construct shape::basic::box ?
		Box(Vec3d origin, Vec3d length)
			: shape::relation::Box(origin, length), shape::collision::Box(origin, length)
		{

		}

		OptionalCollision3D CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
		{
			return shape::collision::Box::CalculateExternalCollisionData(origin, end);
		}

		OptionalCollision3D CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
		{
			return shape::collision::Box::CalculateInternalCollisionData(origin, end);
		}

		bool IsMoleculeInsideBorder(const Vec3d& position) const
		{
			return shape::basic::Box::IsWithinBorder(position);
		}
	};

	class RegionShape
	{
	public:
		virtual OptionalCollision3D CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual OptionalCollision3D CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		void move()
		{

		}
	};

	enum class SurfaceType
	{
		Reflecting, Adsorbing, Absorbing, None
	};

	class Region
	{
	public:
		Region(Vec3d origin, Vec3d length, std::vector<double> diffision_coefficients,
			std::vector<Vec3i> partitions, SurfaceType surface_type)
			: box(origin, length), surface_type(surface_type)
		{
			grids.reserve(Environment::GetNumberOfMoleculeTypes());
			for (int i = 0; i < Environment::GetNumberOfMoleculeTypes(); i++)
			{
				// for a non box shape you would need to do shape.GenerateBoundingBox()
				grids.emplace_back(origin, length, diffision_coefficients.at(i), partitions.at(i));
			}
		}

		RegionShape& GetRegionShape()
		{
			return box;
		}

		const SurfaceType& GetSurfaceType() const
		{
			return surface_type;
		}// probably will become GetSurface().GetType()

		// molecule_a < molecule_b
		// grid neighbours are for diffusion
		// subvolume neighbours are for bi-molecular reactions
		// no need to add subvolume neighbours for neighbouring regions where timestep is smaller
		void AddNeighbours(ID molecule_a, ID molecule_b)
		{
			grids.at(molecule_a).AddNeighbour(grids.at(molecule_b));
		}

		const double& GetTimeStep()
		{
			time_step;
		}
	private:
		SurfaceType surface_type;
		std::vector<Grid> grids;
		Box box;

		double time_step;
		double local_simulation_time; // remove once added to event manager (GetEventTime())
		// surface: Adsorbing, Absorbing, Reflective, None
	};
}
