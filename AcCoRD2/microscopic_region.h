#pragma once
#include "pch.h"
#include "relation_box.h"
#include "collision_box.h"

namespace accord::microscopic
{
	class Box : public shape::relation::Box, public shape::collision::Box
	{
		// can foresee multiple inheritance problem
		// make inheritance virtual ?
		// construct shape::basic::box ?
		Box(Vec3d origin, Vec3d length)
			: shape::relation::Box(origin, length), shape::collision::Box(origin, length)
		{

		}
	};

	class RegionShape
	{
	public:
		virtual std::optional<shape::collision::Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<shape::collision::Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual bool IsMoleculeInsideBorder(const Vec3d& position);
	};

	enum class SurfaceType
	{
		Reflecting, Adsorbing, Absorbing, Passing
	};

	class Region
	{
	public:
		RegionShape& GetRegionShape();

		SurfaceType& GetSurfaceType(); // probably will become GetSurface().GetType()
	private:
		Box box;
		// surface: Adsorbing, Absorbing, Reflective, None
	};
}
