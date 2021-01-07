#pragma once

namespace accord::mesoscopic
{
	class PropensityObject
	{
	public:
		virtual double UpdatePropensity() = 0;
	};

	class LinkedPropensityObjects
	{
	public:
		void RequiresUpdate();

		void Add(PropensityObject* object);

		double UpdatePropensities();

	private:
		bool requires_update;
		std::vector<PropensityObject*> objects;
	};
}