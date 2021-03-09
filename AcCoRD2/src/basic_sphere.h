// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"
#include "basic_shape_3d.h"
#include "basic_box.h"

namespace accord::shape::basic
{
	class Sphere : public Shape3D
	{
	public:
		// construct a sphere from its centre position and radius
		Sphere(Vec3d centre, double radius);

		// create a bounding box which encompasses the sphere
		Box GenerateBoundingBox() const;

		// move the sphere relative to its centre position
		void Move(const Vec3d& centre);

		// change the radius of the sphere
		void Resize(double radius);

		const Vec3d& GetCentre() const;

		const double& GetRadius() const;

		// returns the square of the radius
		const double& GetRadius2() const;

		double CalculateVolume() const;

		double CalculateSurfaceArea() const;

		// returns true of a position lies on or within the surface of the sphere
		// cannot accurately calculate whether a position lies exactly on the sphere due to floating point error
		bool IsWithinOrOnBorder(const Vec3d& position) const;
		
		// convert sphere data to json
		void ToJson(Json& j) const;

		// log sphere data to json format
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Sphere& sphere)
		{
			return os << fmt::format("centre = {}, radius = {}",
				sphere.GetCentre(), sphere.GetRadius());
		}
	private:
		Vec3d centre;
		double radius;
		double radius2;
	};

	// log sphere data to json fromat
	void to_json(Json& j, const Sphere& sphere);
}