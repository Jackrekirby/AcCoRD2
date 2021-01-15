#pragma once
#include "pch.h"

namespace accord
{
	//using MoleculeID = int;
	//using MoleculeIDs = std::vector<int>;

	//using EventID = int;
	//using EventIDs = std::vector<int>;

	//using MicroRegionID = int;
	//using MicroRegionIDs = std::vector<int>;

	using MesoRegionID = int;
	using MesoRegionIDs = std::vector<int>;

	using ReactionID = int;
	using ReactionIDs = std::vector<int>;

	//using ActiveActorID = int;
	//using ActiveActorIDs = std::vector<int>;

	//using PassiveActorID = int;
	//using PassiveActorIDs = std::vector<int>;

	using SubvolumeID = int;
	using SubvolumeIDs = std::vector<int>;
	
	// grids are related to molecule id
	// should subvolumes have an id?
	// should microscopic and mesoscopic regions have their own id type?
	// should non-owning surface have their own id?
}