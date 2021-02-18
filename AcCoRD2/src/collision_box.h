#pragma once
#include "basic_box.h"
#include "collision_surface.h"
#include "collision_rect_surface.h"
#include "collision_shape_3d.h"

namespace accord::shape::collision
{
	// collision box handle the collision of molecules with microscopic box regions
	class Box : virtual public basic::Box, public Shape3D
	{
	public:
		// define the box either with primitive parameters or a basic box
		Box(Vec3d origin, Vec3d length);

		Box(basic::Box box);

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the OUTSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the INSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		// returns the 6 rectangular surfaces which make up the box
		const std::enum_array<Face, RectSurface, 6>& GetFaces() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		// create an array of 6 rectangular surfaces which define the shape of the box
		std::enum_array<Face, RectSurface, 6> GenerateFaces() const;

		// create a side of the box where position contains the position of plane which the surface lies on
		// axis refers to the axis perpendicular to the surface, whilst origin and length contain the definition
		// of the box
		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, 
			const Vec3d& origin, const Vec3d& length) const;
	};

	void to_json(Json& j, const Box& box);
}
