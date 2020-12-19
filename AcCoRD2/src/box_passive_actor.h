#pragma once
#include "passive_actor.h"
#include "relation_box.h"

namespace accord
{
	class PassiveActorBoxShape : public PassiveActorShape, shape::relation::Box
	{
	public:
		PassiveActorBoxShape(shape::basic::Box box)
			: Box(box)
		{

		}

		bool IsMoleculeInsideBorder(const Vec3d& position) const
		{
			return IsMoleculeInsideBorder(position);
		}

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const
		{
			return IsEnveloping(box);
		}

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
		{
			return IsOverlapping(box);
		}
	};

	class BoxPassiveActor : public PassiveActor
	{
	public:
		BoxPassiveActor(shape::relation::Box box, MoleculeIDs molecule_ids,
			double start_time, int priority, EventQueue* event_queue, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		const PassiveActorBoxShape* const GetShape() const;
	private:
		PassiveActorBoxShape box;
	};
}