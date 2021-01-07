#include "pch.h"
#include "propensity_object.h"

namespace accord::mesoscopic
{
	void LinkedPropensityObjects::RequiresUpdate()
	{
		requires_update = true;
	}

	void LinkedPropensityObjects::Add(PropensityObject* object)
	{
		objects.emplace_back(object);
	}

	double LinkedPropensityObjects::UpdatePropensities()
	{
		double delta = 0;
		if (requires_update)
		{
			for (auto& object : objects)
			{
				delta += object->UpdatePropensity();
			}
			requires_update = false;
		}
		return delta;
	}
}