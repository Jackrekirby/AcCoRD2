// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::mesoscopic
{
	class Subvolume;

	class PropensityObject
	{
	public:
		virtual double UpdatePropensity() = 0;
	};

	class LinkedPropensityObjects
	{
	public:
		LinkedPropensityObjects(Subvolume* subvolume);

		void RequiresUpdate();

		void Add(PropensityObject* object);

		void UpdatePropensities();

	private:
		bool requires_update;
		std::vector<PropensityObject*> objects;
		Subvolume* subvolume;
	};
}