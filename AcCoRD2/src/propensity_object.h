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