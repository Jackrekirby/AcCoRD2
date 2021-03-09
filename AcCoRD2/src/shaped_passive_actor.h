// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "passive_actor.h"


namespace accord
{
	class ShapedPassiveActor : public PassiveActor
	{
	public:
		ShapedPassiveActor(std::unique_ptr<PassiveActorShape> shape, const MoleculeIDs& molecule_ids,
			double start_time, int priority, double time_step,
			const PassiveActorID& id, bool record_positions, bool record_time);

		const PassiveActorShape& GetShape() const;
	private:
		std::unique_ptr<PassiveActorShape> shape;
	};
}
