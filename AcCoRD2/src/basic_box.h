// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"
#include "box_faces.h"
#include "basic_shape_3d.h"
#include "vec3i.h"

namespace accord::shape::basic
{
	class Cylinder;
	class Sphere;
	class RectSurface;

	class Box : public Shape3D
	{
	public:
		// construct box from its negative most vertex and its length along each dimension
		Box(Vec3d origin, Vec3d length);

		// construct the boundigng box of a cylinder
		Box(const Cylinder& cylinder);

		// construct the bounding box of a sphere
		Box(const Sphere& sphere);

		// construct the bounding box of a rect surface
		Box(const RectSurface& rect_surface);

		// if 'this' box is divided into a number of subvolumes per axis defined by n_subvolumes
		// then a box 'other' which overlaps 'this' box will overlap all or some of those subvolumes
		// this function returns the indices of the subvolumes which 'other' box overlaps with
		std::vector<int> GetIndices(const Box& other, const Vec3i& n_subvolumes) const;

		// returns itself. Requirement of Shape3D
		Box GenerateBoundingBox() const;

		// returns the overlapping box area between 'this' and 'box'
		Box GenerateOverlapBox(const Box& box) const;

		// returns the bounding box which contains box 'this' box and 'box' box
		Box GenerateBoundingBox(const Box& box) const;

		// change the origin of the box
		void Move(const Vec3d& origin);

		// change the length of the box
		void Resize(const Vec3d& length);

		// returns origin
		const Vec3d& GetOrigin() const;

		// returns origin + length
		const Vec3d& GetEnd() const;

		// returns the length along each dimension
		const Vec3d& GetLength() const;

		// returns origin + 0.5 * length
		Vec3d CalculateCentre() const;

		// returns the volume of the box
		double CalculateVolume() const;

		// retunrs the surface area of the box
		double CalculateSurfaceArea() const;

		// returns true if a point is inside the dimensions of the box, exclusive of its surface
		bool IsWithinBorder(const Vec3d& position) const;

		// returns true if a point is inside the dimensions of the box, inclusive of its surface
		bool IsWithinOrOnBorder(const Vec3d& position) const;

		// returns true if a point is on the surface of the box
		bool IsOnBorder(const Vec3d& position) const;

		// converts box data to json format
		void ToJson(Json& j) const;

		// logs the box data to an output stream
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Box& box)
		{
			return os << fmt::format("origin = {}, length = {}, end = {}", 
				box.GetOrigin(), box.GetLength(), box.GetEnd());
		}
	private:
		Vec3d origin;
		Vec3d length;
		Vec3d end; // origin + length
	};

	// converts box data to json format
	void to_json(Json& j, const Box& box);
}
