// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "propensity_object.h"
#include "mesoscopic_subvolume.h"

namespace accord::mesoscopic
{
	LinkedPropensityObjects::LinkedPropensityObjects(Subvolume* subvolume)
		: requires_update(false), subvolume(subvolume)
	{
	}
	void LinkedPropensityObjects::RequiresUpdate()
	{
		requires_update = true;
	}

	void LinkedPropensityObjects::Add(PropensityObject* object)
	{
		//LOG_INFO("adding object");
		objects.emplace_back(object);
	}

	void LinkedPropensityObjects::UpdatePropensities()
	{
		double delta = 0;
		if (requires_update)
		{
			for (auto& object : objects)
			{
				delta += object->UpdatePropensity();
			}
			requires_update = false;
			//LOG_INFO("new delta propensity = {}", delta);
			//LOG_INFO("new subvolume time = {}", subvolume->GetTime());
			subvolume->UpdateReactionPropensity(delta);
			subvolume->UpdateReactionTime();
		}
		

		
	}
}