// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "shaped_passive_actor.h"

namespace accord
{
	ShapedPassiveActor::ShapedPassiveActor(std::unique_ptr<PassiveActorShape> shape, const MoleculeIDs& molecule_ids, double start_time,
		int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time)
		: PassiveActor(molecule_ids, start_time, priority, time_step, id, record_positions,
			record_time), shape(std::move(shape))
	{
		AddMicroscopicSubvolumesWhichAreInsideActor(molecule_ids);
		AddMesoscopicSubvolumesWhichAreInsideActor();
		CreateFiles();
	}

	const PassiveActorShape& ShapedPassiveActor::GetShape() const
	{
		return *shape;
	}
}
